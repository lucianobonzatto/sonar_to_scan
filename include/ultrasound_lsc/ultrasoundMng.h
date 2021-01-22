#include "ros/ros.h"
#include <tf2_ros/transform_listener.h>
#include <vector>
#include "ultrasound.h"
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/PointCloud2.h"

class ultrasoundMng{
private:
	std::vector<ultrasound*> sensors;
	ros::Publisher lscPub;
	ros::Subscriber lscSub;
	tf2_ros::Buffer tfBuffer;
	tf2_ros::TransformListener tfListener;

public:
	ultrasoundMng(ros::NodeHandle *n);
	~ultrasoundMng();

	void addUltrasound(ros::NodeHandle *n, std::string topic);
	void printSensors();
	void lscCallback(const sensor_msgs::LaserScanConstPtr& cloud_msg);
};
