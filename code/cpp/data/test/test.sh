#!/bin/bash 
echo "HEJ DISPLAY : ${DISPLAY}\n" >> /home/ml/code/crawler/code/cpp/data/robot/ged.txt

#. /home/ml/.bashrc

#/usr/bin/xclock &
. ${HOME}/.bashrc

php robot.php &

