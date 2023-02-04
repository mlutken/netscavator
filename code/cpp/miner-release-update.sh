#!/bin/bash

. ./env.veriquin_cpp
. ../3rdpartysrc/webkit_version.env

#--- Config vars ---
PHP_VER="5.6.12"

# ---------------------
# --- Detect system ---
# ---------------------
BITWIDTH=64

DISTRIB=linux

if type lsb_release >/dev/null 2>&1; then
    # linuxbase.org
    DISTRIB_ID=$(lsb_release -si)
    DISTRIB_RELEASE=$(lsb_release -sr)
elif [ -f /etc/lsb-release ]; then
    . /etc/lsb-release # Get system info
fi

# --- Lowercase DISTRIB_ID ---
DISTRIB_ID=${DISTRIB_ID,,}
DISTRIB=${DISTRIB_ID}${DISTRIB_RELEASE}
export DISTRIB_ID
export DISTRIB_RELEASE
export DISTRIB

echo "DISTRIB_ID     : '${DISTRIB_ID}'"
echo "DISTRIB_RELEASE: '${DISTRIB_RELEASE}'"
echo "DISTRIB        : '${DISTRIB}'"

# ----------------------------------------
# --- Netscavator (new WebKit version) ---
# ----------------------------------------

if [ "" == "${WEBMINER_ROOT_DIR}" ];
then
    WEBMINER_ROOT_DIR=$(cd .. && cd .. && cd .. && cd miners && pwd)
fi


MINERS_INSTALL_DIR=${WEBMINER_ROOT_DIR}/install
SRC_DIR_MANUAL=${VERIQUIN_CPP_DIR}/build_cbs/NetscavatorManual
SRC_DIR_EXE=${VERIQUIN_CPP_DIR}/build_cbs/ninja_release_static
SRC_DIR_LIBS=${VERIQUIN_CPP_DIR}/build_cbs/libs/shared/Release
SRC_DIR_PHP=${VERIQUIN_CPP_DIR}/../3rdparty/php-${PHP_VER}/linux_${BITWIDTH}_release/lib
SRC_DIR_QT=${VERIQUIN_CPP_DIR}/../3rdparty/${WEBKIT_DIR}/linux_${BITWIDTH}_release
SRC_DIR_SCRIPTCRAWL=${VERIQUIN_CPP_DIR}/scriptcrawl
SRC_DATA_DIR=${VERIQUIN_CPP_DIR}/data

DST_DIR_PARENT=${VERIQUIN_CPP_DIR}/..
DST_DIR_NAME=netscavator_${DISTRIB}_${BITWIDTH}
DST_DIR=${DST_DIR_PARENT}/${DST_DIR_NAME}
DST_TAR_FILE=${DST_DIR}.tar.bz2
DST_WEBMINER_INSTALL_DIR=${WEBMINER_ROOT_DIR}/install


echo "MINERS_INSTALL_DIR: ${MINERS_INSTALL_DIR}"
echo "SRC_DIR_EXE: ${SRC_DIR_EXE}"
echo "SRC_DIR_LIBS: ${SRC_DIR_LIBS}"
echo "SRC_DATA_DIR: ${SRC_DATA_DIR}"
echo " "
echo "DST_DIR_PARENT: ${DST_DIR_PARENT}"
echo "DST_DIR_NAME: ${DST_DIR_NAME}"
echo "DST_DIR: ${DST_DIR}"
echo "DST_TAR_FILE: ${DST_TAR_FILE}"
echo "SRC_DIR_QT: ${SRC_DIR_QT}"

echo "Generating Doxygen Manual and reference"
doxygen phpDoxyfile

echo " "

if [ -d ${DST_DIR} ]; then
  echo "Removing old Netscavator release directory : '${DST_DIR}'"
  rm -rf ${DST_DIR}
fi

if [ -f ${DST_TAR_FILE} ]; then
  echo "Removing old Netscavator release tar file  : '${DST_TAR_FILE}'"
  rm -f ${DST_TAR_FILE}
fi


mkdir ${DST_DIR}
mkdir ${DST_DIR}/doc
mkdir ${DST_DIR}/robot
mkdir ${DST_DIR}/data
mkdir -p ${DST_DIR}/data/php/miner_utils
mkdir -p ${DST_DIR}/data/php/miner_templates


if [ -d ${SRC_DIR_LIBS} ]; then
    echo Copy Netscavator files to archive ...
    
    cp -r ${SRC_DIR_MANUAL} ${DST_DIR}
    cp ${SRC_DATA_DIR}/bin/linux/install-xvfb.sh ${DST_DIR}
    cp ${SRC_DATA_DIR}/robot/* ${DST_DIR}/robot/
    cp ${SRC_DATA_DIR}/config/php.ini.in ${DST_DIR}
    cp ${SRC_DATA_DIR}/config/testcreator.cfg.in ${DST_DIR}
    cp ${SRC_DATA_DIR}/config/minercreator.cfg.in ${DST_DIR}
    cp ${SRC_DATA_DIR}/config/crawler.cfg.in ${DST_DIR}
    cp ${SRC_DATA_DIR}/config/netscavator.cfg.in ${DST_DIR}
    cp ${SRC_DATA_DIR}/config/netcreator.cfg.in ${DST_DIR}
    cp ${SRC_DIR_SCRIPTCRAWL}/cpp_crawl/webminer.php ${DST_DIR}
    cp ${SRC_DATA_DIR}/php/miner_utils/*.php ${DST_DIR}/data/php/miner_utils
    cp ${SRC_DATA_DIR}/php/miner_templates/*.php ${DST_DIR}/data/php/miner_templates
    cp ${SRC_DATA_DIR}/bin/linux/*.in ${DST_DIR}
    cp -r ${SRC_DATA_DIR}/icons/ ${DST_DIR}/data
    find ${DST_DIR}/data -name "*.svn" | xargs rm -rf

    cp ${SRC_DIR_LIBS}/cpp_crawl.php ${DST_DIR}

    # --- Copy Qt plugins ---
    cp -r ${SRC_DIR_QT}/plugins/ ${DST_DIR}


    # --- Copy Qt dynamic libraries ---
    ##cp ${SRC_DIR_QT}/lib/lib*.so.5 ${DST_DIR}

    # --- Copy Netscavator libraries and executables ---
    cp ${SRC_DIR_LIBS}/cpp_crawl.so ${DST_DIR}
    cp ${SRC_DIR_LIBS}/libscript_embedding.so ${DST_DIR}
    cp ${SRC_DIR_PHP}/libphp-sleipner5.so ${DST_DIR}
    cp ${SRC_DIR_EXE}/minercreator/minercreator ${DST_DIR}
    cp ${SRC_DIR_EXE}/crawler/crawler ${DST_DIR}
    cp ${SRC_DIR_EXE}/netscavator/netscavator ${DST_DIR}
    cp ${SRC_DIR_EXE}/netcreator/netcreator ${DST_DIR}

    # Copy all dynamic dependencies of libqxcb.so
    ${VERIQUIN_CPP_DIR}/bin/copy_dependencies.sh ${DST_DIR}/plugins/platforms/libqxcb.so ${DST_DIR}

    # Copy all dynamic dependencies of minercreator
    ${VERIQUIN_CPP_DIR}/bin/copy_dependencies.sh ${SRC_DIR_EXE}/netcreator/netcreator ${DST_DIR}

# --- strip files ---
    strip ${DST_DIR}/lib*.so.5

    strip ${DST_DIR}/cpp_crawl.so
    strip ${DST_DIR}/libscript_embedding.so
    strip ${DST_DIR}/libphp-sleipner5.so
    strip ${DST_DIR}/minercreator
    strip ${DST_DIR}/crawler
    strip ${DST_DIR}/netscavator
    strip ${DST_DIR}/netcreator

# --- doc ---
    cp ${VERIQUIN_CPP_DIR}/scriptcrawl/scriptcrawl.i ${DST_DIR}/doc

fi


pushd ${DST_DIR_PARENT}
tar cjvf ${DST_DIR_NAME}.tar.bz2 ${DST_DIR_NAME}
echo "cp ${DST_DIR_NAME}.tar.bz2 ${DST_WEBMINER_INSTALL_DIR}"
cp ${DST_DIR_NAME}.tar.bz2 ${DST_WEBMINER_INSTALL_DIR}

if [ -d ${DST_DIR} ]; then
  echo "Removing Netscavator release directory : '${DST_DIR}'"
  rm -rf ${DST_DIR}
fi

if [ -f ${DST_TAR_FILE} ]; then
  echo "Removing Netscavator release tar file  : '${DST_TAR_FILE}'"
  rm -f ${DST_TAR_FILE}
fi

popd


