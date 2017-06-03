#!/bin/sh
# Bind the USBCAN device
sudo -S slcand -o -c -f -s6 /dev/ttyUSB0 slcan0
sudo -S slcand -o -c -f -s6 /dev/ttyUSB1 slcan1
echo "slcand ok1 "
sleep 0.5
sudo -S ifconfig slcan0 up 
sudo -S ifconfig slcan1 up
echo "slcand ok2 "
sleep 0.5
