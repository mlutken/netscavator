#!/bin/bash 
# Run from crontab for eaxmple by adding a line to /etc/crontab like this:
#
# */5 * * * * username (export DISPLAY=:1 && cd path-to-this-script && ./robot_cronjob.sh)
#
# For running it every 5 minuttes. If your DISPLAY is no :0 then use :1, :2 or whatever it is. Test 
# as user 'username' (the user account that will be running the robot) be issuing "echo $DISPLAY" on a prompt.

. ${HOME}/.bashrc
php robot.php &

