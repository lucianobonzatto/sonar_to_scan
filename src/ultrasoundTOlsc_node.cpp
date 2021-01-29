#include <iostream>
#include "ros/ros.h"
#include "ultrasound_lsc/ultrasoundMng.h"

int main(int argc, char** argv)
{
	ROS_INFO("ultrasoundTOlsc");
	ros::init(argc, argv, "ultrasoundTOlsc");
	ros::NodeHandle n, nhp("~");
	std::vector<std::string> sensors;

	nhp.getParam("ultrasounds", sensors);
	ultrasoundMng teste(&n, nhp.param<std::string>("laserScan/input", "scan"),
                                nhp.param<std::string>("laserScan/output", "scan/ultrasound"));

	for(int i=0; i<sensors.size(); i++){
		teste.addUltrasound(&n, sensors[i]);
	}

	ros::spin();
	return 0;
}
