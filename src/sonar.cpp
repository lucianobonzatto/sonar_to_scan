#include <iostream>
#include "sonar.h"

sonar::sonar(ros::NodeHandle *n, std::string name, std::string frame){
	topic = name;
	this->frame = frame;
	rangeSub = n->subscribe(topic, 1, &sonar::rangeCallback, this);
}

void sonar::rangeCallback(const sensor_msgs::Range::ConstPtr& msg_in){
	value = *msg_in;
}

bool sonar::inLimits(){
	if((value.range < value.max_range) && (value.range > value.min_range)){
		return true;
	}
	return false;
}

float sonar::getRange(){return value.range;}
float sonar::getField(){return value.field_of_view;}
std::string sonar::getTopic(){return topic;}
std::string sonar::getFrame(){return frame;}
