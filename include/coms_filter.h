#ifndef COMS_FILTER_H
#define COMS_FILTER_H

#include <stdio.h> 
#include "ros/ros.h"

#include "joystick2coms/CanMessage.h"
#include "joystick2coms/VehicleMessage.h"
#include "joystick2coms/LWimuID70.h"
#include "joystick2coms/LWimuID71.h"
#include "joystick2coms/LWimuID72.h"
#include "joystick2coms/LWimuID75.h"
#include "joystick2coms/LWimuID76.h"
#include "joystick2coms/LWimuID78.h"
#include "joystick2coms/LWimuID79.h"


namespace comsfilter
{
    	
    struct coms_msg
    {
	ros::Publisher coms_steering_angle;
	ros::Publisher coms_longitude_speed;
    };

    struct LWimu_msg
    {
	ros::Publisher LWimu_ID70;
	ros::Publisher LWimu_ID71;
	ros::Publisher LWimu_ID72;
	ros::Publisher LWimu_ID75;
	ros::Publisher LWimu_ID76;
	ros::Publisher LWimu_ID78;
	ros::Publisher LWimu_ID79;
    };
    
    struct pub_set
    {
	ros::Publisher canpub;
	struct coms_msg coms_msg;
	struct LWimu_msg LWimu_msg;
    };

    //Message from Vehicle
    void vehicleAngle(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame);
    void vehicleSpeed(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame);

    //Message from LWimu
    void LwImuID70(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame);
    void LwImuID71(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame);
    void LwImuID72(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame);
    void LwImuID75(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame);
    void LwImuID76(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame);
    void LwImuID78(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame);
    void LwImuID79(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame);

    //CAN-Filter
    void ros_publish(struct pub_set set, joystick2coms::CanMessage *can_frame);
}


#endif
