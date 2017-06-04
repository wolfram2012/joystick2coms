#include "coms_filter.h"

namespace comsfilter
{

    /*Message from Vehicle*/

    //coms_steering_angle
    void vehicleAngle(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::VehicleMessage data;
	//TODO	
	data.data = can_frame->data[1] + 1;



	//TODO END	
	pub_handle.publish(data);
    }

    //coms_steering_angle
    void vehicleSpeed(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::VehicleMessage data;
	//TODO
	data.data = can_frame->data[1] + 1;



	//TODO END
	pub_handle.publish(data);
    }

    /*Message from Vehicle END*/



    /*Message from LW_IMU*/

    //ID70: AngleX, AngleY, AngleZ, T
    void LwImuID70(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID70 date;
	//TODO
	//data.anglex = can_frame->data[1]*256 + can_frame->data[0];

	//TODO END
	//pub_handle.publish(data);
    }

    //ID70: AngleX, AngleY, AngleZ, T
    void LwImuID71(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID71 date;
	//TODO
	//data.data = can_frame->data[1] + 1;



	//TODO END
	//pub_handle.publish(data);
    }

    //ID70: AngleX, AngleY, AngleZ, T
    void LwImuID72(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID72 date;
	//TODO
	//data.data = can_frame->data[1] + 1;



	//TODO END
	//pub_handle.publish(data);
    }

    //ID70: AngleX, AngleY, AngleZ, T
    void LwImuID75(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID75 date;
	//TODO
	//data.data = can_frame->data[1] + 1;



	//TODO END
	//pub_handle.publish(data);
    }

    //ID70: AngleX, AngleY, AngleZ, T
    void LwImuID76(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID76 date;
	//TODO
	//data.data = can_frame->data[1] + 1;



	//TODO END
	//pub_handle.publish(data);
    }

    //ID70: AngleX, AngleY, AngleZ, T
    void LwImuID78(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID78 date;
	//TODO
	//data.data = can_frame->data[1] + 1;



	//TODO END
	//pub_handle.publish(data);
    }

    //ID70: AngleX, AngleY, AngleZ, T
    void LwImuID79(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID79 date;
	//TODO
	//data.data = can_frame->data[1] + 1;



	//TODO END
	//pub_handle.publish(data);
    }

    /*Message from LW_IMU END*/


    /*CAN-Filter*/
    void ros_publish(struct pub_set set, joystick2coms::CanMessage *can_frame)
    {
	set.canpub.publish(*can_frame);
	switch(can_frame->id)
    	{
	    case 91:
	    	vehicleSpeed(set.coms_msg.coms_steering_angle,can_frame);
	        break;
	    case 92:
	        vehicleAngle(set.coms_msg.coms_longitude_speed,can_frame);
	    	break;
	    case 70:
	        LwImuID70(set.LWimu_msg.LWimu_ID70,can_frame);
	        break;
	    case 71:
	        LwImuID71(set.LWimu_msg.LWimu_ID71,can_frame);
	        break;
	    case 72:
	        LwImuID72(set.LWimu_msg.LWimu_ID72,can_frame);
	        break;
	    case 75:
	        LwImuID75(set.LWimu_msg.LWimu_ID75,can_frame);
	        break;
	    case 76:
	        LwImuID76(set.LWimu_msg.LWimu_ID76,can_frame);
	        break;
	    case 78:
	        LwImuID78(set.LWimu_msg.LWimu_ID78,can_frame);
	        break;
	    case 79:
	        LwImuID79(set.LWimu_msg.LWimu_ID79,can_frame);
	        break;
	    default:
	    	printf("What's this?\n");
    	}

    }


    /*CAN-Filter END*/
}
