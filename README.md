# ultrasound_lsc

Includes ultrasounds valors on a laserScan Topic

## Configuration

Define in `/teste_sensor.yaml` the name of ultrasounds and laserScan topics.

## Topics
### Subscribed

- `/[name]/raw` (`sensor_msgs/Range`) - the ultrasounds input, with the distances in cm

- `/scan` (`sensor_msgs/LaserScan`)  - the laserScan input

- `/tf` - read the ultrasounds position (frame = `/[name]`)

### Published

`/scan/ultrasound` (`sensor_msgs/LaserScan`) - the laserScan output, with the distances in m

## Using

`roslaunch ultrasound_lsc ultrasound_tf.launch`
