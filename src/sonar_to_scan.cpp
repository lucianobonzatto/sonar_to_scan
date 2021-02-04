#include <iostream>
#include "ros/ros.h"
#include "ultrasound_lsc/sonar_manager.h"

int main(int argc, char** argv)
{
	ROS_INFO("Starting sonar to scan node");
	ros::init(argc, argv, "sonar_to_scan");
	ros::NodeHandle nh, nhp("~");
	std::vector<std::string> sensors_topics;
	std::vector<std::string> sensors_frames;

	nhp.getParam("sonar_topics", sensors_topics);
	nhp.getParam("sonar_frames", sensors_frames);
	SonarManager teste(&nh, nhp.param<std::string>("laserScan/input", "scan"),
                                nhp.param<std::string>("laserScan/output", "scan/ultrasound"));

	for(int i=0; i<sensors_frames.size(); i++){
//		std::cout << sensors_frames[i] << std::endl;
		teste.addSonar(&nh, sensors_topics[i], sensors_frames[i]);
	}
	teste.printSensors();

	ros::spin();
	return 0;
}
