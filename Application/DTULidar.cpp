// DTULidar.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread> 
#include <cstdio>

//point cloud visualization
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/range_image/range_image.h>
#include <pcl/visualization/range_image_visualizer.h>

#include <Eigen/Dense> //matrix and vector operations

#include "SerialPort.h"

#define PACKET_SIZE 4 //bytes
//Given by the specs of the sensor
#define MAXDISTANCE 150 //mm
#define MINDISTANCE 30


using namespace std;



char *portName = "\\\\.\\COM8";

const double pi = std::acos(-1);


//String for incoming data
char incomingData[MAX_DATA_LENGTH];
char outcommingData[MAX_DATA_LENGTH];
int readAngle;

/// <summary>
/// struct with all the raw information out of a packet
/// </summary>
struct packet_t {
	float  zAngle;
	float  xAngle;
	uint16_t distance;
};

/// <summary>
/// Takes one packet from the buffer and decodes them
/// </summary>
/// <param name="buffer">The buffer.</param>
/// <returns></returns>
packet_t Decode(std::vector<char> &buffer) {

	packet_t packet;

	//Conversion between number of steps and angle
	float angleConv = 360.0 / 200.0;

	int8_t zAngleRaw = buffer[0];
	packet.zAngle = (float)zAngleRaw * angleConv;

	int8_t xAngleRaw = buffer[1];
	packet.xAngle = (float)xAngleRaw * angleConv;

	packet.distance = *((uint16_t*)(&(buffer[2])));

	buffer.erase(buffer.begin(), buffer.begin() + PACKET_SIZE);

	return packet;
}

/// <summary>
/// Transforms the point from the sensor coordinate frame to the global coordinate frame
/// </summary>
/// <param name="packet">packet struct</param>
/// <returns>PCL XYZRGB point with colour depending on the distance</returns>
pcl::PointXYZRGB TransformPoint(packet_t packet)
{
	//Transform from degrees to radians
	float z = packet.zAngle*(pi / 180);
	float x = packet.xAngle*(pi / 180);

	//Homogeneus coordinates of the point in sensor frame
	Eigen::Vector4f originalVector(0, packet.distance, 0, 1);

	Eigen::Matrix4f transformationMatrix;

	transformationMatrix << cos(z), cos(x)*sin(z), sin(x)*sin(z), 0,
		-sin(z), cos(x)*cos(z), cos(z)*sin(x), 0,
		0, -sin(x), cos(x), 0,
		0, 0, 0, 1;
	/*
	[cos(alpha_z) (cos(alpha_x)*sin(alpha_z))   (sin(alpha_x)*sin(alpha_z)) 0;
	-sin(alpha_z) (cos(alpha_x)*cos(alpha_z))   (cos(alpha_z)*sin(alpha_x)) 0;
	0            -sin(alpha_x)                  cos(alpha_x)               0;
	0             0                             0                          1];*/

	Eigen::Vector4f resultVector = transformationMatrix*originalVector;

	//Give the point a color depending on the distance
	pcl::PointXYZRGB point;
	uint8_t r(255), g(50), b(0);
	point.x=resultVector(0);
	point.y=resultVector(1);
	point.z=resultVector(2);

	r = (uint8_t)((packet.distance-MAXDISTANCE)*(255.0 / (float)(MAXDISTANCE-MINDISTANCE)));
	g = 255 - r;

	uint32_t rgb = (static_cast<uint32_t>(r) << 16 |
	static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
	point.rgb = *reinterpret_cast<float*>(&rgb);

	return point;
}

/// <summary>
/// Initializes the cloud visualization.
/// </summary>
/// <param name="ptrCloud">A pointer to the cloud</param>
/// <returns></returns>
boost::shared_ptr<pcl::visualization::PCLVisualizer> InitializeCloudVisualization(pcl::PointCloud<pcl::PointXYZRGB>::Ptr ptrCloud)
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->setBackgroundColor(0, 0, 0);
	viewer->addPointCloud<pcl::PointXYZRGB> (ptrCloud, "cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");
	viewer->addCoordinateSystem(1.0);
	viewer->initCameraParameters();

	//Add a blue point for the center
	pcl::PointXYZRGB point;
	uint8_t r(0), g(0), b(255);
	point.x = 0;
	point.y = 0;
	point.z = 0;

	uint32_t rgb = (static_cast<uint32_t>(r) << 16 |
		static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
	point.rgb = *reinterpret_cast<float*>(&rgb);

	ptrCloud->points.push_back(point);

	return (viewer);
}

/// <summary>
/// Updates the visualization with a new point
/// </summary>
/// <param name="newPoint">The new point.</param>
/// <param name="viewer">The viewer.</param>
/// <param name="ptrCloud">The PTR cloud.</param>
void UpdateVisualization(pcl::PointXYZRGB newPoint, boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer, pcl::PointCloud<pcl::PointXYZRGB>::Ptr ptrCloud)
{
	ptrCloud->points.push_back(newPoint);

	viewer->updatePointCloud(ptrCloud,"cloud");

	viewer->spinOnce(100);

}

int main()
{
	SerialPort serialport(portName);

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr ptrCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer = InitializeCloudVisualization(ptrCloud);

	if (serialport.isConnected()) cout << "Connected" << endl;
	else cout << "Error. Couldn't connect to device";

	while (serialport.isConnected())
	{
		std::vector<char> buffer;
		//Read all the buffer of the serial port
		int bytesRead = serialport.readSerialPort(incomingData, MAX_DATA_LENGTH);

		//Add the read bytes to an internal buffer
		if (bytesRead > 0)
		{
			for (int i = 0; i < bytesRead; i++)
			{
				buffer.push_back(incomingData[i]);
			}
		}
		//If there is a whole packet in the buffer decode it 
		if (buffer.size() >= PACKET_SIZE) {
			packet_t packet = Decode(buffer);

			//If it is not corrupted add it to the visualization
			if (packet.distance <= MAXDISTANCE) {

				pcl::PointXYZRGB transformedPoint = TransformPoint(packet);

				UpdateVisualization(transformedPoint, viewer, ptrCloud);
			}
		}
		Sleep(10);
	}
	return 0;
}

