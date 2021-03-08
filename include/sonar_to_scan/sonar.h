#include "ros/ros.h"
#include <string>
#include "sensor_msgs/Range.h"

class sonar{
private:
	sensor_msgs::Range value;
	std::string topic;
	std::string frame;
	ros::Subscriber rangeSub;

public:
	sonar(ros::NodeHandle *n, std::string name, std::string frame);
	void rangeCallback(const sensor_msgs::Range::ConstPtr& msg_in);
	bool inLimits();
	float getRange();
	float getField();
    std::string getTopic();
    std::string getFrame();
};
