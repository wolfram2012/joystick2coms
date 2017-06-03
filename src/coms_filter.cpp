#include "coms_filter.h"
#include "joystick2coms/VehicleMessage.h"
#include <stdio.h>

namespace comsfilter
{
    double vehicleAngle(joystick2coms::CanMessage *can_frame)
    {
	double angle = 0;
        printf("canID: %d | canData: ",can_frame->id);
	for(int i=0; i<8; i++)
        {
	    printf("%X ",can_frame->data[i]);
        }
	printf("\n");

///////////TODO////////////	




///////////////////////////
	angle = can_frame->data[1] + 1;
	printf("angle = %f.\n",angle);
	return angle;
    }

    double vehicleSpeed(joystick2coms::CanMessage *can_frame)
    {
	double speed = 0;
        printf("canID: %d | canData: ",can_frame->id);
	for(int i=0; i<8; i++)
        {
	    printf("%X ",can_frame->data[i]);
        }
	printf("\n");
	
///////////TODO////////////




///////////////////////////
	speed = can_frame->data[1] + 1;
	printf("speed = %f.\n",speed);
	return speed;
    }




    void ros_publish(struct pub_set set, joystick2coms::CanMessage *can_frame)
    {
	set.canpub.publish(*can_frame);
	switch(can_frame->id)
    	{
	    case 91:
	    	vehicleSpeed(can_frame);
	        break;
	    case 92:
	        vehicleAngle(can_frame);
	    	break;
	    case 70:
	        
	        break;
	    case 71:
	        
	        break;
	    case 72:
	        
	        break;
	    case 75:
	        
	        break;
	    case 76:
	        
	        break;
	    case 78:
	        
	        break;
	    case 79:
	        
	        break;
	    default:
	    	printf("What's this?\n");
    }

    }
}
