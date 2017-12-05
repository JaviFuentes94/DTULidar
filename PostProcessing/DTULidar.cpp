// DTULidar.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread> 
#include <cstdio>



#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/pcd_io.h>

#include <Eigen/Dense>

#include "SerialPort.h"
#include "PacketDecoder.h"


using namespace std;



char *portName = "\\\\.\\COM8";

const double pi = std::acos(-1);

pcl::PointCloud<pcl::PointXYZ> cloud;


//String for incoming data
char incomingData[MAX_DATA_LENGTH];
char outcommingData[MAX_DATA_LENGTH];
int readAngle;

pcl::PointXYZ TransformPoint(PacketDecoder::packet_t packet)
{
	float z = packet.zAngle*(pi / 180);
	float x = packet.xAngle*(pi / 180);

	Eigen::Vector4f originalVector(0, packet.distance, 0, 1);

	Eigen::Matrix4f transformationMatrix;

	transformationMatrix << cos(z), cos(x)*sin(z), sin(x)*sin(z), 0,
		-sin(z), cos(x)*cos(z), cos(z)*sin(x), 0,
		0, -sin(x), cos(x), 0,
		0, 0, 0, 1;

	Eigen::Vector4f resultVector = transformationMatrix*originalVector;
	cout << "Resultant point= " << resultVector << endl;

	pcl::PointXYZ point(resultVector(0), resultVector(1), resultVector(2));

	return point;
}

void ReadUsb(SerialPort &serialport) {
	
	while (serialport.isConnected())
	{
		int bytesRead = serialport.readSerialPort(incomingData, MAX_DATA_LENGTH);

		//puts(incomingData);
		if (bytesRead == 6) {
			PacketDecoder::packet_t packet = PacketDecoder::Decode(incomingData);
			
			pcl::PointXYZ transformedPoint;
			transformedPoint = TransformPoint(packet);


			//printf("zAngle: %d \n", packet.zAngle);
			//printf("yAngle: %d \n", packet.yAngle);
			//printf("Distance: %d \n", packet.distance);
		}
		Sleep(100);
	}
}


/*
[cos(alpha_z) (cos(alpha_x)*sin(alpha_z))   (sin(alpha_x)*sin(alpha_z)) 0;
-sin(alpha_z) (cos(alpha_x)*cos(alpha_z))   (cos(alpha_z)*sin(alpha_x)) 0;
0            -sin(alpha_x)                  cos(alpha_x)               0;
0             0                             0                          1];*/

boost::shared_ptr<pcl::visualization::PCLVisualizer> InitializeVisualization()
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->setBackgroundColor(0, 0, 0);
	pcl::PointCloud<pcl::PointXYZ>::Ptr ptrCloud(&cloud);
	viewer->addPointCloud<pcl::PointXYZ> (ptrCloud, "cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
	viewer->addCoordinateSystem(1.0);
	viewer->initCameraParameters();
	return (viewer);
}

void UpdateVisualization(pcl::PointXYZ newPoint, boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer)
{
	cloud.push_back(newPoint);

	pcl::PointCloud<pcl::PointXYZ>::Ptr ptrCloud(&cloud);

	viewer->updatePointCloud(ptrCloud,"cloud");

	viewer->spinOnce(100);

	//viewer.showCloud(ptrCloud);
}

int main(int argc, char** argv)
{
	/*PacketDecoder::packet_t packet;
	packet.xAngle = 30;
	packet.zAngle = 90;
	packet.distance = 1;

	TransformPoint(packet);*/

	cloud.push_back(pcl::PointXYZ(rand(), rand(), 0));
	cloud.push_back(pcl::PointXYZ(rand(), rand(), 1));


	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer = InitializeVisualization();
	

	int nPoints = 100;
	for (int i = 0; i < nPoints; i++) 
	{
		UpdateVisualization(pcl::PointXYZ(rand(), rand(), i), viewer);
		cout << "New point received";
		getchar();
	}

	/*pcl::PointCloud<pcl::PointXYZ>::Ptr ptrCloud(&cloud);

	viewer.showCloud(ptrCloud);
	while (!viewer.wasStopped())
	{

	}*/
	getchar();
	return (0);
}


/*int main()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	
	if (pcl::io::loadPCDFile<pcl::PointXYZ>("test_pc.pcd", *cloud) == -1) //* load the file
	{
		PCL_ERROR("Couldn't read file test_pcd.pcd \n");
		cout << "Error";
		return (-1);
	}
	std::cout << "Loaded "
		<< cloud->width * cloud->height
		<< " data points from test_pcd.pcd with the following fields: "
		<< std::endl;
	for (size_t i = 0; i < cloud->points.size(); ++i)
		std::cout << "    " << cloud->points[i].x
		<< " " << cloud->points[i].y
		<< " " << cloud->points[i].z << std::endl;

	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
	viewer.showCloud(cloud);
	while (!viewer.wasStopped())
	{
		cout << "Meow";
		getchar();
	}
	return 0;
}
*/
/*
int main()
{
	SerialPort serialport(portName);
	if (serialport.isConnected()) cout << "Connected" << endl;
	else cout << "Error. Couldn't connect to device";

	thread usbThread(ReadUsb, serialport);
	usbThread.join();

	getchar();
	return 0;
}
*/
