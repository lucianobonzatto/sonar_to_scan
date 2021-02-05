# sonar_to_scan

Transform sonar readings into a laser scan topic

## Configuration

Define in `/config/[name].yaml` the frame and topic of the sonar, the desired scan params and add it to the launch file.

## Topics
### Subscribed

- parameter sonar_topics (`sensor_msgs/Range`) - the ultrasounds input, with the distances in centimeters

- `/tf` - sonar sensor transform (`sonar_frames`)

### Published

- parameter /laserScan/output (`sensor_msgs/LaserScan`) - the laserScan output, with the distances in meters

## How to use

`roslaunch sonar_to_scan sonar_to_scan.launch`
