#ifndef COMS_FILTER_H
#define COMS_FILTER_H

#include <stdio.h> 
#include "ros/ros.h"
#include "joystick2coms/VehicleMessage.h"
#include "joystick2coms/CanMessage.h"


namespace comsfilter
{
    	
    struct coms_msg
    {
	ros::Publisher coms_steering_angle;
	ros::Publisher coms_longitude_speed;
    };

    struct Wimu_msg
    {
	int i;
    };
    
    struct pub_set
    {
	ros::Publisher canpub;
	struct coms_msg coms_msg;
	struct Wimu_msg Wimu_msg;
//	struct imu_msg imu_msg;
    };


    double vehicleAngle(joystick2coms::CanMessage *can_frame);
    double vehicleSpeed(joystick2coms::CanMessage *can_frame);

    void ros_publish(struct pub_set set, joystick2coms::CanMessage *can_frame);
}


#endif
