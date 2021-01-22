#include "ultrasound.h"

ultrasound::ultrasound(ros::NodeHandle *n, std::string name){
	topic = name;
	frame = name;
	rangeSub = n->subscribe(topic, 1, &ultrasound::rangeCallback, this);
}

void ultrasound::rangeCallback(const sensor_msgs::Range::ConstPtr& msg_in){
	value = *msg_in;
}

float ultrasound::getRange(){return value.range;}
float ultrasound::getField(){return value.field_of_view;}
std::string ultrasound::getTopic(){return topic;}
std::string ultrasound::getFrame(){return frame;}
