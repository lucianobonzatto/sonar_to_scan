#include <iostream>
#include "ros/ros.h"
#include "ultrasound_lsc/sonar_manager.h"

int main(int argc, char** argv)
{
	ROS_INFO("Starting sonar to scan node");
	ros::init(argc, argv, "sonar_to_scan");
	ros::NodeHandle nh;
	std::vector<std::string> sensors_topics;
	std::vector<std::string> sensors_frames;

	nh.getParam("sonar_topics", sensors_topics);
	nh.getParam("sonar_frames", sensors_frames);
	SonarManager teste(&nh, nh.param<std::string>("laserScan/input", "scan"),
                                nh.param<std::string>("laserScan/output", "scan/ultrasound"));

	for(int i=0; i<sensors_topics.size(); i++){
		teste.addSonar(&nh, sensors_topics[i], sensors_frames[i]);
	}

	ros::spin();
	return 0;
}
