# Joystick2coms

## Control COMS with Joystick
Having fun controling the EV COMS in our Lab with Joystick!

## Installation
This ROS package had been tested on ROS Kinect on Ubuntu 16.04   
We use Lawicel CANUSB(http://www.can232.com) in our Lab to fulfill CAN_Bus communication   
We tested two kinds of Joystick(Logitech F310 and Logitech F710)

### Install Can-utils
The test tool for Lawicel CANUSB
>	`sudo apt-get install can-utils`
### Install Joystick drivers
Install joystick drivers package for your ROS:
>`sudo apt-get install ros-kinetic-joystick-drivers` 

If failed to find the package "ros-kinect-joystick-drivers":
>	`sudo apt-cache search ros-kinetic`  
  `sudo apt-get update`  
  `sudo apt-get install ros-kinetic-joystick-drivers`   

### Install joystick2coms
Download the code:
>	`# In your cankin_ws/`  
`cd src/`  
`git clone https://github.com/wolfram2012/joystick2coms.git`  

Build:
>	`# In you catkin_ws/src/`  
`cd ..`  
`catkin_make`  

You got it !
## Run the Programme
Make sure you have sourced `setup.bash` in your catkin_ws. Then run the roslaunch to make CAN-Bus and Joystick ready:
>	`roslaunch joystick2coms joy2coms.launch `

Maybe you will be asked for passward for opening the CANUSB. Don't worry, be happy.![](https://github.com/wolfram2012/Store-Big-Guys/raw/master/joystick2coms/README/timg.jpg "Don't Worry") 

If there is an error of:  
*  *Roslaunch got a 'No such file or directory' error while attempting to run:terminator -x*
  
Just install terminator, it's a good terminal:
> `sudo apt-get install terminator`

If there is an error of:  
*  *[ERROR]: Couldn't open joystick /dev/input/js0. Will retry every second.*    

That you just forget to plugin your joystick  

When you roslaunch successfully, you will find a reconfig window:   
<div>
<img src="https://github.com/wolfram2012/Store-Big-Guys/raw/master/joystick2coms/README/rqt_reconfig1.png" width = "527" height = "334" alt="123" align="center" />   
</div>  
You can set the CAN-Bus ID to send and regulate the rate of CAN-Bus(Defalut:Stop)  


Then you can control our COMS (Control Program Version: BC_v1.2)

If you want to check the CAN message using CAN-utils:
>	`candump slcan0`

## Control tips(example joystick: Logitech F710)  

|     Module Number     |   Name            | Function |
|:---------------------:|:------------------------:|:-------------:|
| **1** | Throttle Command| Accel Pedal  |
| **2** | Brake Command| Brake Pedal  |
| **3** | Steering Mode | Pressed:Large Angle Mode； Eased： Old Woman Mode  |
| **4** | Lamps Command |  ←：left； →：right; ↓:double flash; ↑:cancel  |
| **5** | Gear Command |  A:drive; B:neutral; Y:reverse |
| **6** | Steering Command |  Steering Wheel  |
<div>
<img src="https://github.com/wolfram2012/Store-Big-Guys/raw/master/joystick2coms/README/joystick2.png" width = "423" height = "255" alt="123" />
<img src="https://github.com/wolfram2012/Store-Big-Guys/raw/master/joystick2coms/README/joystick1.png" width = "423" height = "255" alt="123" />
</div>    




You are welcome.
