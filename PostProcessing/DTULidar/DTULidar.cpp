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

	/*transformationMatrix << cos(z), cos(x)*sin(z), sin(x)*sin(z), 0,
		-sin(z), cos(x)*cos(z), cos(z)*sin(x), 0,
		0, -sin(x), cos(x), 0,
		0, 0, 0, 1;*/

	transformationMatrix << cos(z), cos(x)*sin(z), sin(x)*sin(z), 0,
		-sin(z), sin(x)*sin(z), cos(z)*sin(x), 0,
		0, cos(x), cos(x), 0,
		0, 0, 0, 1;


	Eigen::Vector4f resultVector = transformationMatrix*originalVector;
	//cout << "Resultant point= " << resultVector << endl;

	pcl::PointXYZ point(resultVector(0), resultVector(1), resultVector(2));

	return point;
}


/*
[cos(alpha_z) (cos(alpha_x)*sin(alpha_z))   (sin(alpha_x)*sin(alpha_z)) 0;
-sin(alpha_z) (cos(alpha_x)*cos(alpha_z))   (cos(alpha_z)*sin(alpha_x)) 0;
0            -sin(alpha_x)                  cos(alpha_x)               0;
0             0                             0                          1];*/

boost::shared_ptr<pcl::visualization::PCLVisualizer> InitializeVisualization(pcl::PointCloud<pcl::PointXYZ>::Ptr ptrCloud)
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->setBackgroundColor(0, 0, 0);
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(ptrCloud, 0, 255, 0);
	viewer->addPointCloud<pcl::PointXYZ> (ptrCloud, single_color, "cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");
	viewer->addCoordinateSystem(1.0);
	viewer->initCameraParameters();
	return (viewer);
}

void UpdateVisualization(pcl::PointXYZ newPoint, boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer, pcl::PointCloud<pcl::PointXYZ>::Ptr ptrCloud)
{
	ptrCloud->points.push_back(newPoint);

	viewer->updatePointCloud(ptrCloud,"cloud");

	viewer->spinOnce(100);

	//viewer.showCloud(ptrCloud);
}

/*int main(int argc, char** argv)
{
	PacketDecoder::packet_t packet;
	packet.xAngle = 30;
	packet.zAngle = 90;
	packet.distance = 1;

	TransformPoint(packet);

	printf("int %d \n",sizeof(int));
	printf("float %d \n", sizeof(float));

	pcl::PointCloud<pcl::PointXYZ>::Ptr ptrCloud(new pcl::PointCloud<pcl::PointXYZ>);

	ptrCloud->points.push_back(pcl::PointXYZ(rand(), rand(), 0));
	ptrCloud->points.push_back(pcl::PointXYZ(rand(), rand(), 1));


	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer = InitializeVisualization(ptrCloud);
	

	int nPoints = 100;
	for (int i = 0; i < nPoints; i++) 
	{
		UpdateVisualization(pcl::PointXYZ(rand(), rand(), i), viewer, ptrCloud);
		cout << "New point received";
		Sleep(1000);
	}

	//pcl::PointCloud<pcl::PointXYZ>::Ptr ptrCloud(&cloud);

	//viewer.showCloud(ptrCloud);
	//while (!viewer.wasStopped())
	//{

	//}
	getchar();
	return (0);
}
*/

int main()
{
	SerialPort serialport(portName);

	pcl::PointCloud<pcl::PointXYZ>::Ptr ptrCloud(new pcl::PointCloud<pcl::PointXYZ>);
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer = InitializeVisualization(ptrCloud);

	if (serialport.isConnected()) cout << "Connected" << endl;
	else cout << "Error. Couldn't connect to device";

	while (serialport.isConnected())
	{
		int bytesRead = serialport.readSerialPort(incomingData, MAX_DATA_LENGTH);

		//printf_s("Bytes read %d \n", bytesRead);
		//puts(incomingData);
		if (bytesRead == PACKET_SIZE) {
			PacketDecoder::packet_t packet = PacketDecoder::Decode(incomingData);

			printf("zAngle: %f \n", packet.zAngle);
			printf("xAngle: %f \n", packet.xAngle);
			printf("Distance: %d \n", packet.distance);

			pcl::PointXYZ transformedPoint = TransformPoint(packet);

			UpdateVisualization(transformedPoint, viewer, ptrCloud);

			
		}
		Sleep(10);
	}

	getchar();
	return 0;
}

