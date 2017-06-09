#include "ros/ros.h"
#include "tf/tf.h"
#include "tf/transform_broadcaster.h"
#include "geometry_msgs/PoseStamped.h"

double pose_x = 0;
double pose_y = 0;

double quat_x = 0;
double quat_y = 0;
double quat_z = 0;
double quat_w = 1;

void poseCallback(const geometry_msgs::PoseStamped& point)
{
    pose_x = point.pose.position.x;
    pose_y = point.pose.position.y;
    //ROS_INFO("I heard somthing");
    quat_x = point.pose.orientation.x;
    quat_y = point.pose.orientation.y;
    quat_z = point.pose.orientation.z;
    quat_w = point.pose.orientation.w;
    //ROS_INFO("pose_x: %f; pose_y: %f.",pose_x, pose_y);
}

void poseInit()
{
    static tf::TransformBroadcaster broadcaster;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(1, 1, 0) );
    tf::Quaternion q(0, 0, 0, 1);

    transform.setRotation(q);
    broadcaster.sendTransform(
	    tf::StampedTransform(
		transform,ros::Time::now(),"map","coms"));
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "coms_tf_broadcaster");
    ros::NodeHandle n;
    tf::TransformBroadcaster broadcaster;
    ros::Subscriber tf_sub = n.subscribe("/base_pose",100, poseCallback);
    ros::Rate r(100);
    
    double th = 0;
    while(n.ok())
    {
	th += 0.25;
	broadcaster.sendTransform(
         tf::StampedTransform(
           tf::Transform( tf::Quaternion(quat_x, quat_y, quat_z, quat_w), tf::Vector3(pose_x, pose_y, 0)),
           ros::Time::now(),"map", "coms"));
	ROS_INFO("while-> pose_x: %f; pose_y: %f.",pose_x, pose_y);
        r.sleep();
	ros::spinOnce();
    }
//    poseInit();
    

    
    return 0;
}
