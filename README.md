# ultrasound_lsc

Includes sonar readings into a laser scan topic

## Configuration

Define in `/config/teste_sensor.yaml` the name of the sonar and scan topics, the sonar frames and remember to include this file in the launch file.

## Topics
### Subscribed

- `/[sonar_topic_name]` (`sensor_msgs/Range`) - the ultrasounds input, with the distances in centimeters

- `/scan` (`sensor_msgs/LaserScan`)  - the laserScan input

- `/tf` - sonar sensor transform

### Published

`/scan/ultrasound` (`sensor_msgs/LaserScan`) - the laserScan output, with the distances in meters

## How to use

`roslaunch ultrasound_lsc sonar_to_scan.launch`
