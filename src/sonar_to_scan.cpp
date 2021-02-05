#include <iostream>
#include "ros/ros.h"
#include "sonar_to_scan/sonar_manager.h"

int main(int argc, char** argv)
{
	ROS_INFO("Starting sonar to scan node");
	ros::init(argc, argv, "sonar_to_scan");
	ros::NodeHandle nh, nhp("~");
	std::vector<std::string> sensors_topics;
	std::vector<std::string> sensors_frames;
	sensor_msgs::LaserScan laser_output;
	int frequency;

	nhp.getParam("sonar_topics", sensors_topics);
	nhp.getParam("sonar_frames", sensors_frames);
	nhp.getParam("frequency", frequency);

	nhp.getParam("laserScan/frame_id", laser_output.header.frame_id);
	nhp.getParam("laserScan/angle_increment", laser_output.angle_increment);
	nhp.getParam("laserScan/time_increment", laser_output.time_increment);
	nhp.getParam("laserScan/scan_time", laser_output.scan_time);
	nhp.getParam("laserScan/range_min", laser_output.range_min);
	nhp.getParam("laserScan/range_max", laser_output.range_max);
	laser_output.angle_min = -M_PI;
	laser_output.angle_max = M_PI;

	SonarManager teste(&nh, nhp.param<std::string>("laserScan/output", "scan/ultrasound"),
				laser_output);

	for(int i=0; i<sensors_frames.size(); i++){
//		std::cout << sensors_frames[i] << std::endl;
		teste.addSonar(&nh, sensors_topics[i], sensors_frames[i]);
	}
	teste.printSensors();
	teste.loop(frequency);

	return 0;
}
