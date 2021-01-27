# ultrasound_lsc
Includes ultrasounds valors on a laserScan Topic

## Configuration
In src/ultrasoundTOlsc_node.cpp, include the ultrasounds using:

`void ultrasoundMng::addUltrasound(ros::NodeHandle *n, std::string name);`

the [name] is used to create de topic and the tf frame of the sensor.

## Topics

### Subscribed
- `/[name]` (`sensor_msgs/Range`) - the ultrasound input, with the distances in cm

- `/scan` (`sensor_msgs/LaserScan`)  - the laserScan input

- `/tf` - read the ultrasounds position (frame = `/[name]`)

### Published
`/scan/ultrasound` (`sensor_msgs/LaserScan`) - the laserScan output, with the distances in m

## Using
`rosrun ultrasound_lsc ultrasoundTOlsc`

`roslaunch ultrasound_lsc ultrasound_tf.launch`
