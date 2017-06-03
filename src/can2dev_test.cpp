#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"
#include "ros/timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <dynamic_reconfigure/server.h>
#include <joystick2coms/joystickConfig.h>

#include "data2msg.h"



uint8_t lamps = 0;
uint8_t stb_mode = 0;
uint8_t gear = 0;
uint8_t st = 127;
uint8_t th = 0;
uint8_t bk = 0;
uint8_t data2send[8] = {0};
float steering = 0;
float brake = 0;
float throttle = 0;

int can_id = 103;
int can_speed_mode = 1;
double can_speed = 3600;

ros::Timer timer;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("I heard: [%s]",msg->data.c_str());
    
    uint8_t a[8] = {0,1,2,3,4,5,156,255};
    data2msg(100,a);
}

void Joy2cansend(const sensor_msgs::Joy&joymsg)
{

    steering = joymsg.axes[3];
    brake = joymsg.axes[2];
    throttle = joymsg.axes[5];
    
    //Gear Change
    if(joymsg.buttons[1]==1)
      gear = 1;
    else if(joymsg.buttons[0]==1)
      gear = 2;
    else if(joymsg.buttons[3]==1)
      gear = 3;
    else
      gear = 0;

    //steering mode change
    stb_mode = (uint8_t)joymsg.buttons[4];

    //lamps change
    if(joymsg.axes[7]==-1)
      lamps = 3;
    else if(joymsg.axes[6]==1)
      lamps = 1;
    else if(joymsg.axes[6]==-1)
      lamps = 2;
    else if(joymsg.axes[7]==1)
      lamps = 4;
    else
      lamps = 0;

    st = (uint8_t)(255*(steering+1)/2);
    th = (uint8_t)(255*(1-throttle)/2);
    bk = (uint8_t)(255*(1-brake)/2);
    
}

void callback(const ros::TimerEvent& event)
{
    data2send[0] = st;
    data2send[1] = stb_mode;
    data2send[2] = lamps;
    data2send[3] = gear;
    data2send[4] = th;
    data2send[5] = bk;
    data2send[6] = 0;
    data2send[7] = 0;
    data2msg(can_id,data2send);
}

void reconfigCallback(joystick2coms::joystickConfig &config, uint32_t level)
{
    can_id = config.CAN_ID_Decimal;
    can_speed_mode = config.CAN_Speed_Hz;

    if (can_speed_mode == 4)
        can_speed = 0.02;
    else if(can_speed_mode == 3)
        can_speed = 0.05;
    else if(can_speed_mode == 2)
        can_speed = 0.1;
    else if(can_speed_mode == 1)
        can_speed = 1;
    else if(can_speed_mode == 0)
        can_speed = 3600;
    else
        can_speed = 3600;
    timer.setPeriod(ros::Duration(can_speed),true);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "can2dev");
    ros::NodeHandle n;

    timer = n.createTimer(ros::Duration(3600), callback);
    
    ros::Subscriber sub = n.subscribe("canmsg2send",1000,chatterCallback);
    ros::Subscriber joy = n.subscribe("joy",1000,Joy2cansend);

    dynamic_reconfigure::Server<joystick2coms::joystickConfig>server;
    dynamic_reconfigure::Server<joystick2coms::joystickConfig>::CallbackType f;
    f = boost::bind(&reconfigCallback, _1, _2);
    server.setCallback(f);

    
    //timer.setPeriod(ros::Duration(0.1),true);
    ros::spin();

    return 0;
}
