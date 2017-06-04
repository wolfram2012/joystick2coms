#include "coms_filter.h"

namespace comsfilter
{

    /*Message from Vehicle*/

    //coms: steering_angle and speed
    void vehicleMessage(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::VehicleMessage data;
	//TODO
	data.steering = 0;
	data.speed = 0;

	//TODO END
	pub_handle.publish(data);
    }

    /*Message from Vehicle END*/



    /*Message from LW_IMU*/

    //ID70: AngleX, AngleY, AngleZ, T
    void LwImuID70(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID70 data;
	//TODO
	data.anglex = 0;
	data.angley = 0;
	data.anglez = 0;
	data.T = 0;

	//TODO END
	pub_handle.publish(data);
    }

    //ID71: AccelX, AccelY, AccelZ
    void LwImuID71(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID71 data;
	//TODO
	data.accelx = 0;
	data.accely = 0;
	data.accelz = 0;

	//TODO END
	pub_handle.publish(data);
    }

    //ID72: CompassX, CompassY, CompassZ
    void LwImuID72(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID72 data;
	//TODO
	data.compassx = 0;
	data.compassy = 0;
	data.compassz = 0;

	//TODO END
	pub_handle.publish(data);
    }

    //ID75: GPSmode, StarNum, HDOP, High, UTC:h/m/s/ms
    void LwImuID75(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID75 data;
	//TODO
	data.GPSmode = 0;
	data.starNum = 0;
	data.HDOP = 0;
	data.hight = 0;
	data.UTCh = 0;
	data.UTCm = 0;
	data.UTCs = 0;
	data.UTCms = 0;

	//TODO END
	pub_handle.publish(data);
    }

    //ID76: GPSL, GPSR
    void LwImuID76(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID76 data;
	//TODO
	data.GPSl = 0;
	data.GPSr = 0;

	//TODO END
	pub_handle.publish(data);
    }

    //ID78: Roll, Pitch, Yaw, PZ
    void LwImuID78(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID78 data;
	//TODO
	data.roll = 0;
	data.pitch = 0;
	data.yaw = 0;
	data.pz = 0;

	//TODO END
	pub_handle.publish(data);
    }

    //ID79: PositionX, PositionY
    void LwImuID79(ros::Publisher pub_handle, joystick2coms::CanMessage *can_frame)
    {
	joystick2coms::LWimuID79 data;
	//TODO
	data.positionx = 0;
	data.positiony = 0;

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
	    case 93:
	        vehicleMessage(set.coms_msg.coms_vehicle_msg,can_frame);
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
