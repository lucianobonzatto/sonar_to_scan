#include <iostream>
#include <math.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "sonar_manager.h"

SonarManager::SonarManager(ros::NodeHandle *n, std::string outputTopic, sensor_msgs::LaserScan laser_output):
tfListener(tfBuffer){
	lscPub = n->advertise<sensor_msgs::LaserScan>(outputTopic, 1, this);
	laserMsg = laser_output;
}

SonarManager::~SonarManager(){
	for(int i = 0; i < sensors.size(); i++)	{
		delete sensors[i];
	}
	sensors.clear();
}

void SonarManager::addSonar(ros::NodeHandle *n, std::string name, std::string frame){
	sonar* p = new sonar(n, name, frame);
	sensors.push_back(p);
}

void SonarManager::printSensors(){
	for(int i = 0; i < sensors.size(); i++){
		std::cout << sensors[i]->getTopic() << ", " << sensors[i]->getFrame() << ", " << sensors[i]->getRange() << std::endl;
	}
}

void SonarManager::includePointToLaser(geometry_msgs::PointStamped point, sensor_msgs::LaserScan* laserScan){
	double range = hypot(point.point.y, point.point.x);
	double angle = atan2(point.point.y, point.point.x);

	if((angle >= laserScan->angle_min && angle <= laserScan->angle_max) && (range >= laserScan->range_min && range <= laserScan->range_max))
	{
		int index = (angle - laserScan->angle_min) / laserScan->angle_increment;
		if(laserScan->ranges[index] > range)
			laserScan->ranges[index] = range;
	}
	else
		std::cout << "Out of scan range error:" << std:: endl
			  << "angle: " << angle << "range: " << range << std:: endl;

}

void SonarManager::loop(int frequency){
	while(ros::ok()){
		sensor_msgs::LaserScan laser_output = laserMsg;
		uint32_t ranges_size = std::ceil((laser_output.angle_max - laser_output.angle_min) / laser_output.angle_increment);
		laser_output.ranges.assign(ranges_size, std::numeric_limits<double>::infinity());

		ros::spinOnce();

		for(int i = 0; i < sensors.size(); i++){
			
			//std::cout << "------------------------" << std:: endl;
			//std::cout << sensors[i]->getTopic() << ", " << sensors[i]->getFrame() << ", " << sensors[i]->getRange() << std::endl;

			if(!sensors[i]->inLimits()){
				continue;
			}

			//read the ultrasound position
			geometry_msgs::TransformStamped transform;
			try {
		                transform = tfBuffer.lookupTransform(laser_output.header.frame_id, sensors[i]->getFrame(), ros::Time(0));
	            	} catch (tf2::TransformException ex) {
        	        	ROS_WARN("tf error: %s", ex.what());
        	        	continue;
        	    	}

/*			include the ultrasounds to laser_output */
			geometry_msgs::PointStamped point_SensorFrame, point_LaserFrame;


/*			include only the central point */
			point_SensorFrame.point.x = sensors[i]->getRange();
			tf2::doTransform(point_SensorFrame, point_LaserFrame, transform);	//tranform to laser frame
			includePointToLaser(point_LaserFrame, &laser_output);			//include the left point

/*			include all points of the cone
			for(float j=0; j < sensors[i]->getField()/4; j=j+0.01)
			{
				point_SensorFrame.point.x = sensors[i]->getRange();
				point_SensorFrame.point.y = tan(j)*sensors[i]->getRange();
				tf2::doTransform(point_SensorFrame, point_LaserFrame, transform);	//tranform to laser frame
				includePointToLaser(point_LaserFrame, &laser_output);			//include the left point

				point_SensorFrame.point.y *= -1;
				tf2::doTransform(point_SensorFrame, point_LaserFrame, transform);	//tranform to laser frame
				includePointToLaser(point_LaserFrame, &laser_output);			//include the right point
			}*/
		}

		laser_output.header.stamp = ros::Time::now();
		lscPub.publish(laser_output);
		usleep(1000000/frequency);
	}
}
