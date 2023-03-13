#! /bin/bash

set -x
set -e


# building in temporary directory to keep system clean
# use RAM disk if possible (as in: not building on CI system like Travis, and RAM disk is available)

if [ "$CI" == "" ] && [ -d /dev/shm ]; then

    TEMP_BASE=/dev/shm

else

    TEMP_BASE=/tmp

fi


BUILD_DIR=$(mktemp -d -p "$TEMP_BASE" appimage-build-XXXXXX)


# make sure to clean up build dir, even if errors occur
cleanup () {
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
    fi
}

trap cleanup EXIT


# store repo root as variable

REPO_ROOT=$(readlink -f $(dirname $(dirname $0)))

OLD_CWD=$(readlink -f .)

echo "OLD_CWD: '$OLD_CWD'"


# switch to build dir

pushd "$BUILD_DIR"


# configure build files with CMake
# we need to explicitly set the install prefix, as CMake's default is /usr/local for some reason...
# build project and install files into AppDir
cmake "$REPO_ROOT" -DCMAKE_INSTALL_PREFIX=/usr
make -j$(nproc)
make install DESTDIR=AppDir

cp /usr/lib/x86_64-linux-gnu/nss/* AppDir/usr/lib
cp ./bin/qtwebengine_devtools_resources.pak AppDir/usr/bin/
cp ./bin/qtwebengine_resources_100p.pak AppDir/usr/bin/
cp ./bin/qtwebengine_resources_200p.pak AppDir/usr/bin/
cp ./bin/qtwebengine_resources.pak AppDir/usr/bin/

# now, build AppImage using linuxdeploy and linuxdeploy-plugin-qt

# download linuxdeploy and its Qt plugin
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
wget https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage

# make them executable
chmod +x linuxdeploy*.AppImage


# make sure Qt plugin finds QML sources so it can deploy the imported files
# export QML_SOURCES_PATHS="$REPO_ROOT"/src


# initialize AppDir, bundle shared libraries for QtQuickApp, use Qt plugin to bundle additional resources, and build AppImage, all in one single command
mv AppDir/usr/share/applications/netscavator.desktop AppDir/usr/share/applications/netscavator.desktop.bak
cp AppDir/usr/share/pixmaps/netcreator.png AppDir/
./linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage
# move built netcreator AppImage back into original CWD
mv netcreator*.AppImage "$OLD_CWD"

mv AppDir/usr/share/applications/netscavator.desktop.bak AppDir/usr/share/applications/netscavator.desktop
rm AppDir/netcreator.png
rm AppDir/AppRun
rm AppDir/usr/share/applications/netcreator.desktop
rm AppDir/usr/share/pixmaps/netcreator.png
cp AppDir/usr/share/pixmaps/netscavator.png AppDir/
./linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage
# move built netscavator AppImage back into original CWD
mv netscavator*.AppImage "$OLD_CWD"


