# ultrasound_lsc

Includes sonar readings into a laser scan topic

## Configuration

Define in `/config/teste_sensor.yaml` the name of the sonar and scan topics and add it to the launch file.

## Topics
### Subscribed

- `/[name]/raw` (`sensor_msgs/Range`) - the ultrasounds input, with the distances in centimeters

- `/scan` (`sensor_msgs/LaserScan`)  - the laserScan input

- `/tf` - sonar sensor transform (frame = `/[name]`)

### Published

`/scan/ultrasound` (`sensor_msgs/LaserScan`) - the laserScan output, with the distances in meters

## How to use

`roslaunch ultrasound_lsc ultrasound_tf.launch`
