#! /bin/bash
STARTUP_DIR=`pwd`
INSTALL_XVFB_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${INSTALL_XVFB_DIR}

sudo cp ./xvfb.service /etc/systemd/system
sudo apt-get install xvfb
sudo systemctl enable /etc/systemd/system/xvfb.service
sudo service xvfb start

cd ${STARTUP_DIR} # Return to our starting dir

# # To run the crawler for example do like this!
# DISPLAY=:99 run_crawler /home/ml/code/miners/scripts/cycling/dk/pythonpro.dk.php 

