# ultrasound_lsc
Includes ultrasounds valors on a laserScan Topic

## Configuration
In src/ultrasoundTOlsc_node.cpp, include the ultrasounds using:

`void ultrasoundMng::addUltrasound(ros::NodeHandle *n, std::string name);`

the [name] is used to create de topic and the tf frame of the sensor.

## Topics

### Subscribed
`/[name]` - the ultrasound input (sensor_msgs/Range)

`/scan` - the laserScan input (sensor_msgs/LaserScan) 

`/tf` - read the ultrasounds position

### Published
`/scan/ultrasound` - the laserScan output (sensor_msgs/LaserScan) 
