#include "ros/ros.h"
#include "ultrasound_lsc/ultrasoundMng.h"

int main(int argc, char** argv)
{
	ROS_INFO("ultrasoundTOlsc");
	ros::init(argc, argv, "ultrasoundTOlsc");
	ros::NodeHandle n;

	ultrasoundMng teste(&n, "/scan", "scan/ultrasound");
	teste.addUltrasound(&n, "/ultrasound_1");
	teste.addUltrasound(&n, "/ultrasound_2");
	teste.addUltrasound(&n, "/ultrasound_3");
	teste.addUltrasound(&n, "/ultrasound_4");
	teste.addUltrasound(&n, "/ultrasound_5");
	teste.addUltrasound(&n, "/ultrasound_6");


	ros::spin();
/*	while(ros::ok())
	{
	//	teste.printSensors();
//		sleep(1);
		ros::spinOnce();
	}*/
	return 0;
}
