#!/bin/bash

#
SAVE_DIR=`pwd`

# --------------------------------------
# --- Detect linux distribution name ---
# --------------------------------------
APT_GET=`which apt-get`
DNF=`which dnf`
SYSNAME="Suse"
if [ "${APT_GET}" != "" ]; then  SYSNAME="Ubuntu";
elif [ "${DNF}" != "" ]; then  SYSNAME="Fedora";
fi

echo "System name: $SYSNAME"
if [ "$SYSNAME" == "Ubuntu" ]
then
    # ---------------------------
    # --- Ubuntu Install libs ---
    # ---------------------------
	echo "System is Ubuntu"
    # --- Get php version info ---
    . ${THEHIVE_SETUP_DIR}/system-php-version.sh
	sudo apt-get install -y ruby ruby-dev qtbase5-dev qt5-default qt5-doc qtbase5-examples qtbase5-doc-html libqt5webchannel5-dev qtdeclarative5-private-dev glib2.0
	sudo apt-get install -y  qtpositioning5-dev libqt5sensors5-dev libqt5gstreamer-dev libqt5multimediawidgets5
	sudo apt-get install -y  qtbase5-private-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
	sudo apt-get install -y build-essential perl flex gperf bison cmake ninja-build libfontconfig1-dev libicu-dev libsqlite3-dev zlib1g-dev libjpeg-dev libxslt1-dev libxml2-dev libhyphen-dev
	sudo apt-get install -y p7zip-full ruby build-essential perl  git bison gperf flex libicu-dev libsqlite3-dev libphonon-dev libxkbcommon-dev libpulse-dev libasound2-dev libxcb1 libxcb1-dev libx11-xcb1 libwebp-dev libxslt1-dev libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-sync0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-glx0-dev libpcre++-dev "^libxcb.*" libx11-xcb-dev libglu1-mesa-dev libxrender-dev libfontconfig1-dev libxcomposite-dev libpcre3-dev libpcre++-dev
	sudo apt-get -y libgcrypt11-dev
	sudo apt-get -y libtasn1-6-dev
	sudo apt-get install -y software-properties-gtk
	sudo apt-get install -y graphviz doxygen
	sudo apt-get install -y php7*
    sudo apt-get install -y php${SYSTEM_PHP_VERSION}-dev
    sudo apt-get install -y libpng12-0
	sudo apt-get install -y libpng12-dev
	sudo apt-get install -y libpng-dev
	sudo apt-get install -y libssl-dev
	sudo apt-get install -y libgstreamer-plugins-*
	sudo apt-get install -y libwoff-dev
	sudo apt-get install -y swig
	sudo apt-get install -y php7.2-dev
	sudo apt-get install -y libonig-dev



###	sudo apt-get install -y php5-cli p7zip-full ruby build-essential perl python git bison gperf flex libicu-dev libsqlite3-dev libphonon-dev libxkbcommon-dev libpulse-dev libasound2-dev libxcb1 libxcb1-dev libx11-xcb1 libwebp-dev libxslt1-dev libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-sync0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-glx0-dev libpcre++-dev "^libxcb.*" libx11-xcb-dev libglu1-mesa-dev libxrender-dev libfontconfig1-dev libxcomposite-dev libpcre3-dev libpcre++-dev
elif [ "$SYSNAME" == "Fedora" ]
then
    # -----------------------------------------
    # --- Fedora/CentOS/Redhat Install libs ---
    # -----------------------------------------
	echo "System is Fedora/Centos/Redhat"
	# gperftools-devel
	sudo dnf install -y qt-develop
	sudo dnf install -y pcre-devel libxml2-devel libxml++-devel php-cli perl bison gperf python ruby ruby-devel libsqlite3x-devel libjpeg-turbo-devel libxslt-devel fontconfig-devel libwebp-devel libXcomposite-devel libXrender-devel gstreamer1-devel gstreamer1-plugins-base-devel hyphen-devel openssl-devel

	# Try to locate all qt5 devel packages and install them
	# FIXMENM, jus commented out while finding all the packages we need :)
	sudo dnf search qt5-qt | grep "^qt5.*-devel.x86_64" | cut -d " " -f 1 | xargs sudo dnf install -y

elif [ "$SYSNAME" == "Suse" ]
then
    # -------------------------
    # --- SuSe Install libs ---
    # -------------------------
	echo "System is Suse"
fi


cd ${SAVE_DIR}


