#include "ros/ros.h"
#include <tf2_ros/transform_listener.h>
#include <vector>
#include "sonar.h"
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/PointCloud2.h"
#include "geometry_msgs/PointStamped.h"
#include <limits>

class SonarManager{
private:
	std::vector<sonar*> sensors;
	ros::Publisher lscPub;
	tf2_ros::Buffer tfBuffer;
	tf2_ros::TransformListener tfListener;
	sensor_msgs::LaserScan laserMsg;

	void includePointToLaser(geometry_msgs::PointStamped point, sensor_msgs::LaserScan* laserScan);

public:
	SonarManager(ros::NodeHandle *n, std::string outputTopic, sensor_msgs::LaserScan laser_output);
	~SonarManager();

	void addSonar(ros::NodeHandle *n, std::string name, std::string frame);
	void printSensors();
	void lscCallback(const sensor_msgs::LaserScanConstPtr& cloud_msg);
	void loop(int frequency);
};
