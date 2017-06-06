#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "geometry_msgs/PoseStamped.h"


void poseCallback(const geometry_msgs::PoseStamped& point)
{
    static tf::TransformBroadcaster broadcaster;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(point.pose.position.x, point.pose.position.y, 0) );
    tf::Quaternion q(
    	point.pose.orientation.x,
    	point.pose.orientation.y,
    	point.pose.orientation.z,
    	point.pose.orientation.w );

    transform.setRotation(q);
    broadcaster.sendTransform(
	    tf::StampedTransform(
		transform,ros::Time::now(),"map","coms"));
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "coms_tf_broadcaster");
    ros::NodeHandle n;

    ros::Subscriber tf_sub = n.subscribe("base_pose",10,&poseCallback);

    ros::spin();
    return 0;
}
