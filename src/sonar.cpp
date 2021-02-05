#include <iostream>
#include "sonar.h"

sonar::sonar(ros::NodeHandle *n, std::string name, std::string frame){
	topic = name;
	this->frame = frame;
//	rangeSub = n->subscribe(topic, 1, &sonar::rangeCallback, this);
	rangeSub = n->subscribe(topic, 1, &sonar::rangeCallback, this);
}

void sonar::rangeCallback(const sensor_msgs::Range::ConstPtr& msg_in){
	value = *msg_in;
//	value.range /= 100;
//	value.min_range /= 100;
//	value.max_range /= 100;
//	std::cout << topic << ", " << frame << ", " << value.range << std::endl;
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
