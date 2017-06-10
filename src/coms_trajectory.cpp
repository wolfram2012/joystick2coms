#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/PoseStamped.h"
#include "tf/tf.h"
#include <tf/transform_listener.h>
#include "joystick2coms/VehicleMessage.h"

#include "visualization_msgs/Marker.h"

double steering = 0.0;
double speed = 0.0;

double dis = 0;	
double kk  = 0;
double delta_x  = 0;
double delta_y  = 0;
double delta_th = 0;

double pi = 3.141593;
ros::Publisher pose_pub;
ros::Publisher tra_pub;
nav_msgs::Path trajectory;


void vehicleMessage(const joystick2coms::VehicleMessage& msg)
{
    steering = (pi/180) * msg.steering;
    speed = msg.speed;
}

void transformPoint(const tf::TransformListener &listener)
{
    dis = speed * 0.05;	
    kk  = asin((dis * tan(steering)/3.06));
    delta_x  = dis*sin(kk);
    delta_y  = dis*cos(kk);;
    delta_th = 2*kk;

    geometry_msgs::PoseStamped vb_point;
    vb_point.header.stamp = ros::Time();
    vb_point.header.frame_id = "coms";
    vb_point.pose.position.x = delta_x;
    vb_point.pose.position.y = delta_y;
    vb_point.pose.position.z = 0;
    geometry_msgs::Quaternion quat = tf::createQuaternionMsgFromYaw(delta_th);
    vb_point.pose.orientation = quat;

    try
    {
	geometry_msgs::PoseStamped global_point;
	listener.transformPose("map", vb_point, global_point);
	global_point.header.frame_id = "map";
	pose_pub.publish(global_point);
	
	trajectory.header.frame_id = "map";
        trajectory.poses.push_back(global_point);
        tra_pub.publish(trajectory);

    }
    catch(tf::TransformException& ex)
    {
	ROS_ERROR(" %s", ex.what());
//	ROS_INFO("something happen");
    }	

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "trajectory");
    ros::NodeHandle n;
    pose_pub = n.advertise<geometry_msgs::PoseStamped>("base_pose",100);
    tra_pub = n.advertise<nav_msgs::Path>("trajectory",1);
    ros::Subscriber sub = n.subscribe("/coms/vehiclemessage",1000,vehicleMessage);

    tf::TransformListener listener(ros::Duration(0.05));  
    ros::Timer timer = n.createTimer(ros::Duration(0.05), boost::bind(&transformPoint, boost::ref(listener)));
    
    //trajectory.header.stamp = ros::Time();
    //trajectory.header.frame_id = "coms";

    ros::spin();
    return 0;
}
