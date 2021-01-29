#include "ultrasound.h"

ultrasound::ultrasound(ros::NodeHandle *n, std::string name){
	topic = name;
	frame = name;
//	rangeSub = n->subscribe(topic, 1, &ultrasound::rangeCallback, this);
	rangeSub = n->subscribe(topic + "/raw", 1, &ultrasound::rangeCallback, this);
}

void ultrasound::rangeCallback(const sensor_msgs::Range::ConstPtr& msg_in){
	value = *msg_in;
	value.range /= 100;
	value.min_range /= 100;
	value.max_range /= 100;
}

bool ultrasound::inLimits(){
	if((value.range <= value.max_range) && (value.range >= value.min_range)){
		return true;
	}
	return false;
}

float ultrasound::getRange(){return value.range;}
float ultrasound::getField(){return value.field_of_view;}
std::string ultrasound::getTopic(){return topic;}
std::string ultrasound::getFrame(){return frame;}
