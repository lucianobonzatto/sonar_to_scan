#include "ros/ros.h"
#include <string>
#include "sensor_msgs/Range.h"

class ultrasound{
private:
	sensor_msgs::Range value;
	std::string topic;
	std::string frame;
	ros::Subscriber rangeSub;

public:
	ultrasound(ros::NodeHandle *n, std::string name);
	void rangeCallback(const sensor_msgs::Range::ConstPtr& msg_in);
	float getRange();
	float getField();
        std::string getTopic();
        std::string getFrame();
};
