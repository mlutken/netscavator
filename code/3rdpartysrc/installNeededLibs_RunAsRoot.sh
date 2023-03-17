#!/bin/bash

# ICU Configure cmd: ./icu4c/source/runConfigureICU  Linux --enable-static --disable-shared
# Qt configure cmd : ./configure -nomake examples -nomake tests -cmake-generator "Unix Makefiles"

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
	sudo apt-get install -y swig
	sudo apt-get install -y libmd4c-dev

    # Fot Qt compilation
	sudo apt-get install -y libfontconfig1-dev
	sudo apt-get install -y libfreetype6-dev
	sudo apt-get install -y libx11-dev
	sudo apt-get install -y libx11-xcb-dev
	sudo apt-get install -y libxext-dev
	sudo apt-get install -y libxfixes-dev
	sudo apt-get install -y libxi-dev
	sudo apt-get install -y libxrender-dev
	sudo apt-get install -y libxcb1-dev
	sudo apt-get install -y libxcb-glx0-dev
	sudo apt-get install -y libxcb-keysyms1-dev
	sudo apt-get install -y libxcb-image0-dev
	sudo apt-get install -y libxcb-shm0-dev
	sudo apt-get install -y libxcb-icccm4-dev
	sudo apt-get install -y libxcb-sync-dev
	sudo apt-get install -y libxcb-xfixes0-dev
	sudo apt-get install -y libxcb-shape0-dev
	sudo apt-get install -y libxcb-randr0-dev
	sudo apt-get install -y libxcb-render-util0-dev
	sudo apt-get install -y libxcb-util-dev
	sudo apt-get install -y libxcb-xinerama0-dev
	sudo apt-get install -y libxcb-xkb-dev
	sudo apt-get install -y libxkbcommon-dev
	sudo apt-get install -y libxkbcommon-x11-dev
        sudo apt install -Y libclang-10-dev
	sudo apt-get -y install qt6-base-dev
	sudo apt-get -y install qt6-webengine-dev
	sudo apt-get -y install libqt6webchannel6-dev
	sudo apt-get -y install qt6-webengine-dev-tools
	sudo apt-get -y install libqt6webenginecore6-bin

    # --- For Webengine ---
    # Node js: https://www.techiediaries.com/ubuntu/install-nodejs-npm-on-ubuntu-20-04/
    curl -sL https://deb.nodesource.com/setup_18.x | sudo -E bash -
    curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | sudo apt-key add -
    sudo apt-get update
    sudo apt-get install -y nodejs
    sudo apt-get install -y libsnappy-dev
    sudo apt-get install -y libdrm-dev
    sudo apt-get install -y libxshmfence-dev
#     sudo apt-get install -y libharfbuzz-dev
    sudo apt-get install -y libminizip-dev
    sudo apt-get install -y libminizip-dev
    sudo apt-get install -y liblcms2-dev
    sudo apt-get install -y libopus-dev
    sudo apt-get install -y libvpx-dev



#     Configuring 'qtwebengine'
# -- CMAKE_BUILD_TYPE was set to: 'Release'
# -- Could NOT find Gn (missing: Gn_EXECUTABLE) (Required is exact version "6.2.4")
# -- Checking for module 'snappy'
# --   No package 'snappy' found
# -- Could NOT find Snappy (missing: SNAPPY_LIBRARY SNAPPY_INCLUDE_DIR)
# -- Found Nodejs: /usr/bin/node (found suitable version "18.15.0", minimum required is "10.19")
# -- Checking for module 'libdrm'
# --   No package 'libdrm' found
# -- Checking for module 'xshmfence'
# --   No package 'xshmfence' found
# -- Checking for module 'x11'
# --   Found x11, version 1.6.9
# -- Checking for modules 'harfbuzz>=2.4.0;harfbuzz-subset>=2.4.0'
# --   No package 'harfbuzz-subset' found
# -- Checking for module 'libjpeg'
# --   Found libjpeg, version 2.0.3
# -- Checking for module 'minizip'
# --   No package 'minizip' found
# -- Checking for module 're2'
# --   No package 're2' found
# -- Checking for modules 'icu-uc>=68;icu-i18n>=68'
# --   Requested 'icu-uc >= 68' but version of icu-uc is 66.1
# --   Requested 'icu-i18n >= 68' but version of icu-i18n is 66.1
# -- Checking for module 'lcms2'
# --   No package 'lcms2' found
# -- Checking for module 'opus>=1.3.1'
# --   No package 'opus' found
# -- Checking for module 'vpx>=1.10.0'
# --   No package 'vpx' found
# -- Checking 'ulimit -n'
#  -- Open files limit 65535




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


