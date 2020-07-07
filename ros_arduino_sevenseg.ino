// #include <ros.h>
// #include <ros/time.h>
// #include <sensor_msgs/Range.h>
//
// #include "ros_arduino_sevenseg.hpp"


///* ROS *///
// namespace ros {
// typedef NodeHandle_<ArduinoHardware, 0, 6, 0, 128> NodeHandle_L;
// }
//
// ros::NodeHandle_L nh;


void setup() {
    // nh.getHardware()->setBaud(115200);
    // nh.initNode();
    display.begin();
}

void loop() {
    while (1) {  // For decreasing overhead time
        // if (nh.connected()) {
        // }
        // delay(10);
        // nh.spinOnce();

        display.print(3.14);
    }
}
