# ultrasound_lsc

Includes ultrasounds valors on a laserScan Topic

## Configuration

In /teste_sensor.yaml, define the name of laserScan topics and ultrasounds.

## Topics
### Subscribed

- `/[name]/raw` (`sensor_msgs/Range`) - the ultrasounds input, with the distances in cm

- `/scan` (`sensor_msgs/LaserScan`)  - the laserScan input

- `/tf` - read the ultrasounds position (frame = `/[name]`)

### Published

`/scan/ultrasound` (`sensor_msgs/LaserScan`) - the laserScan output, with the distances in m

## Using

`roslaunch ultrasound_lsc ultrasound_tf.launch`
