#include <iostream>
#include <math.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "ultrasoundMng.h"
#include "geometry_msgs/PointStamped.h"

ultrasoundMng::ultrasoundMng(ros::NodeHandle *n):
tfListener(tfBuffer){
	lscPub = n->advertise<sensor_msgs::LaserScan>("scan/ultrasound", 1, this);
	lscSub = n->subscribe("/scan", 1, &ultrasoundMng::lscCallback, this);
}

ultrasoundMng::~ultrasoundMng(){
	for(int i = 0; i < sensors.size(); i++)	{
		delete sensors[i];
	}
	sensors.clear();
}

void ultrasoundMng::addUltrasound(ros::NodeHandle *n, std::string name){
	ultrasound* p = new ultrasound(n, name);
	sensors.push_back(p);
}

void ultrasoundMng::printSensors(){
	for(int i = 0; i < sensors.size(); i++){
		std::cout << sensors[i]->getTopic() << " -> " << sensors[i]->getRange() << std::endl;
	}
}

void ultrasoundMng::lscCallback(const sensor_msgs::LaserScanConstPtr& laser_msg){
	sensor_msgs::LaserScan output;
	output.header = laser_msg->header;
	output.angle_min = -M_PI;
	output.angle_max = M_PI;
	output.angle_increment = M_PI / 180.0;
	output.time_increment = 0.0;
	output.scan_time = 1.0/30.0;
	output.range_min = 0.65;
	output.range_max = 200.0;

	uint32_t ranges_size = std::ceil((output.angle_max - output.angle_min) / output.angle_increment);
	output.ranges.assign(ranges_size, std::numeric_limits<double>::infinity());

	for(int i=0; i<laser_msg->ranges.size(); i++)
	{
		int j = ((i * laser_msg->angle_increment + laser_msg->angle_min) - output.angle_min)/output.angle_increment;
		output.ranges[j] = laser_msg->ranges[i];
	}

/*	for (sensor_msgs::PointCloud2ConstIterator<float> iter_x(*cloud_msg, "x"), iter_y(*cloud_msg, "y"),iter_z(*cloud_msg, "z");
		iter_x != iter_x.end(); ++iter_x, ++iter_y, ++iter_z)
	{

		if (std::isnan(*iter_x) || std::isnan(*iter_y) || std::isnan(*iter_z))
		{
			ROS_INFO("rejected for nan in point(%f, %f, %f)\n", *iter_x, *iter_y, *iter_z);
			continue;
		}

		if (*iter_z > 0.5 || *iter_z < -0.3)
		{
			ROS_INFO("rejected for height %f not in range (%f, %f)\n", *iter_z, 0.5, -0.3);
			continue;
		}

		double range = hypot(*iter_x, *iter_y);
		if (range < 0.65)
		{
			ROS_INFO("rejected for range %f below minimum value %f. Point: (%f, %f, %f)", range, 0.65, *iter_x, *iter_y, *iter_z);
			continue;
	    	}
		if (range > 200.0)
		{
			ROS_INFO("rejected for range %f above maximum value %f. Point: (%f, %f, %f)", range, 200.0, *iter_x,*iter_y, *iter_z);
		continue;
		}

		double angle = atan2(*iter_y, *iter_x);
		if (angle < output.angle_min || angle > output.angle_max)
		{
			ROS_INFO("rejected for angle %f not in range (%f, %f)\n", angle, output.angle_min, output.angle_max);
			continue;
		}

		// overwrite range at laserscan ray if new range is smaller
		int index = (angle - output.angle_min) / output.angle_increment;
		if (range < output.ranges[index])
		{
			output.ranges[index] = range;
		}
	}*/

	for(int i = 0; i < sensors.size(); i++){

		geometry_msgs::TransformStamped transform;
		try {
                transform = tfBuffer.lookupTransform(laser_msg->header.frame_id,
                                                     sensors[i]->getFrame(),
                                                     ros::Time(0));
            	} catch (tf2::TransformException ex) {
                	ROS_WARN("erro no tf do sensor: %s", ex.what());
                	continue;
            	}

		//mudança de frame
		geometry_msgs::PointStamped pt_SensorFrame, pt_LaserFrame;
		pt_SensorFrame.point.x = sensors[i]->getRange();
		tf2::doTransform(pt_SensorFrame, pt_LaserFrame, transform);

		//inclui o ponto no LaserScan
		double range = hypot(pt_LaserFrame.point.y, pt_LaserFrame.point.x);
		double angle = atan2(pt_LaserFrame.point.y, pt_LaserFrame.point.x);

		if((angle >= output.angle_min && angle <= output.angle_max) && (range >= output.range_min && range <= output.range_max))
		{
			int index = (angle - output.angle_min) / output.angle_increment;
			if(output.ranges[index] > range)
					output.ranges[index] = range;
			if(output.ranges[index+1] > range)
					output.ranges[index+1] = range;
			if(output.ranges[index-1] > range)
					output.ranges[index-1] = range;

/*			for(int j = 0; j <= sensors[i]->getField()/2; j++)
			{
				if(output.ranges[index+j] > range)
					output.ranges[index+j] = range;

				if(output.ranges[index-j] > range)
					output.ranges[index-j] = range;
			}*/	
		}
		
//		pcl::PointXYZ pcl_point;
//		pcl_point.x = pt_CloundFrame.point.x;
//		pcl_point.y = pt_CloundFrame.point.y;
//		pcl_point.z = pt_CloundFrame.point.z;
//		pcl_cloud->points.push_back(pcl_point);
//		++(pcl_cloud->width);
	}

	lscPub.publish(output);
}
