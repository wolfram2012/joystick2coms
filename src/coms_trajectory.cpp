#include "ros/ros.h"
#include "ros/console.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/PoseStamped.h"
#include "tf/tf.h"
#include "joystick2coms/VehicleMessage.h"

double steering = 0.0;
double speed = 0.0;

double pi = 3.141593;

void vehicleMessage(const joystick2coms::VehicleMessage& msg)
{
    steering = (pi/180) * msg.steering;
    speed = msg.speed;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "trajectory");
    ros::NodeHandle n;
    ros::Publisher tra_pub = n.advertise<nav_msgs::Path>("trajectory",1);
    ros::Subscriber sub = n.subscribe("/coms/vehiclemessage",1000,vehicleMessage);

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = current_time;

    nav_msgs::Path trajectory;
    trajectory.header.stamp = current_time;
    trajectory.header.frame_id = "coms";

    double x  = 0.0;
    double y  = 0.0;
    double th = 0.0;
    double vx = 0.1;
    double vy = -0.1;
    double vth = 0.1;
    double dt = 0.1;

    ros::Rate loop_rate(10);

    while(ros::ok())
    {
	current_time = ros::Time::now();
	double dis = speed * 0.1;	
	double kk = asin((dis * tan(steering)/3.06));
	double delta_x  = dis*sin(kk);
	double delta_y  = dis*cos(kk);;
	double delta_th = 360/pi * kk;

	x  +=  delta_x;
	y  +=  delta_y;
	th +=  delta_th;

	ROS_INFO("x = %f. y = %f",x,y);

	geometry_msgs::PoseStamped temp_pose;
	temp_pose.pose.position.x = x;
	temp_pose.pose.position.y = y;

	geometry_msgs::Quaternion quat = tf::createQuaternionMsgFromYaw(th);
	temp_pose.pose.orientation.x = quat.x;
	temp_pose.pose.orientation.y = quat.y;
	temp_pose.pose.orientation.z = quat.z;
	temp_pose.pose.orientation.w = quat.w;

	temp_pose.header.stamp = current_time;
	temp_pose.header.frame_id = "coms";

	trajectory.poses.push_back(temp_pose);

	tra_pub.publish(trajectory);
	ros::spinOnce();

	last_time = current_time;
	loop_rate.sleep();
	
    }
    return 0;
}
