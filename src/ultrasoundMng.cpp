#include <iostream>
#include <math.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "ultrasoundMng.h"

ultrasoundMng::ultrasoundMng(ros::NodeHandle *n, std::string inputTopic, std::string outputTopic):
tfListener(tfBuffer){
	lscPub = n->advertise<sensor_msgs::LaserScan>(outputTopic, 1, this);
	lscSub = n->subscribe(inputTopic, 1, &ultrasoundMng::lscCallback, this);
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
	output.angle_increment = laser_msg->angle_increment;
	output.time_increment = laser_msg->time_increment;
	output.scan_time = laser_msg->scan_time;
	output.range_min = laser_msg->range_min;
	output.range_max = laser_msg->range_max;

	uint32_t ranges_size = std::ceil((output.angle_max - output.angle_min) / output.angle_increment);
	output.ranges.assign(ranges_size, std::numeric_limits<double>::infinity());

	//include the laser_msg to output
	for(int i=0; i<laser_msg->ranges.size(); i++)
	{
		int j = ((i * laser_msg->angle_increment + laser_msg->angle_min) - output.angle_min)/output.angle_increment;
		output.ranges[j] = laser_msg->ranges[i];
	}

	for(int i = 0; i < sensors.size(); i++){
		if(!sensors[i]->inLimits()){
	               	ROS_WARN("sensor %i out of ultrasound limits", i+1);
			continue;
		}

		//read the ultrasound position
		geometry_msgs::TransformStamped transform;
		try {
                transform = tfBuffer.lookupTransform(laser_msg->header.frame_id,
                                                     sensors[i]->getFrame(),
                                                     ros::Time(0));
            	} catch (tf2::TransformException ex) {
                	ROS_WARN("tf error: %s", ex.what());
                	continue;
            	}

/*		include the ultrasounds to output */
		geometry_msgs::PointStamped pt_SensorFrame, pt_LaserFrame;

/*			include only the central point */
		pt_SensorFrame.point.x = sensors[i]->getRange();
		tf2::doTransform(pt_SensorFrame, pt_LaserFrame, transform);	//tranform to laser frame
		includePointToLaser(pt_LaserFrame, &output);			//include the left point

/*			include all points of the cone
		for(float j=0; j < sensors[i]->getField()/4; j=j+0.01)
		{
			pt_SensorFrame.point.x = sensors[i]->getRange();
			pt_SensorFrame.point.y = tan(j)*sensors[i]->getRange();
			tf2::doTransform(pt_SensorFrame, pt_LaserFrame, transform);	//tranform to laser frame
			includePointToLaser(pt_LaserFrame, &output);			//include the left point

			pt_SensorFrame.point.y *= -1;
			tf2::doTransform(pt_SensorFrame, pt_LaserFrame, transform);	//tranform to laser frame
			includePointToLaser(pt_LaserFrame, &output);			//include the right point
		}*/
	}

	lscPub.publish(output);
}

void ultrasoundMng::includePointToLaser(geometry_msgs::PointStamped point, sensor_msgs::LaserScan* laserScan){
	double range = hypot(point.point.y, point.point.x);
	double angle = atan2(point.point.y, point.point.x);

	if((angle >= laserScan->angle_min && angle <= laserScan->angle_max) && (range >= laserScan->range_min && range <= laserScan->range_max))
	{
		int index = (angle - laserScan->angle_min) / laserScan->angle_increment;
		if(laserScan->ranges[index] > range)
			laserScan->ranges[index] = range;
	}
}
