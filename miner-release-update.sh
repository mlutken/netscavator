#!/bin/bash

#--- Config vars ---
PHP_VER="5.6.12"

CRAWLER_REPOSITORY_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CODE_ROOT_DIR="$( dirname "${CRAWLER_REPOSITORY_ROOT_DIR}" )"
CODE_BUILD_ROOT_DIR="${CODE_ROOT_DIR}/_build"
CRAWLER_BUILD_ROOT_DIR="${CODE_BUILD_ROOT_DIR}/crawler"

WEBMINER_ROOT_DIR=${CODE_ROOT_DIR}/miners
VERIQUIN_CODE_DIR=${CRAWLER_REPOSITORY_ROOT_DIR}/code
VERIQUIN_CPP_DIR=${VERIQUIN_CODE_DIR}/cpp

. ${VERIQUIN_CODE_DIR}/3rdpartysrc/webkit_version.env

# --- Make sure code is built ---
bash ${CRAWLER_REPOSITORY_ROOT_DIR}/build.sh -b=release

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



# -------------------
# --- Netscavator ---
# -------------------

MINERS_INSTALL_DIR=${WEBMINER_ROOT_DIR}/install
SRC_DIR_MANUAL=${CRAWLER_BUILD_ROOT_DIR}/NetscavatorManual
SRC_DIR_EXE=${CRAWLER_BUILD_ROOT_DIR}/bin
SRC_DIR_LIBS=${CRAWLER_BUILD_ROOT_DIR}/bin
SRC_DIR_PHP=${VERIQUIN_CODE_DIR}/3rdparty/php-${PHP_VER}/linux_${BITWIDTH}_release/lib
SRC_DIR_QT=${VERIQUIN_CODE_DIR}/3rdparty/${WEBKIT_DIR}/linux_${BITWIDTH}_release
SRC_DIR_SCRIPTCRAWL=${VERIQUIN_CPP_DIR}/scriptcrawl
SRC_DATA_DIR=${VERIQUIN_CPP_DIR}/data

DST_DIR_NAME=netscavator_${DISTRIB}_${BITWIDTH}
DST_DIR=${CRAWLER_BUILD_ROOT_DIR}/${DST_DIR_NAME}
DST_TAR_FILE=${DST_DIR}.tar.bz2
DST_WEBMINER_INSTALL_DIR=${WEBMINER_ROOT_DIR}/install


echo "DISTRIB_ID            : ${DISTRIB_ID}"
echo "DISTRIB_RELEASE       : ${DISTRIB_RELEASE}"
echo "DISTRIB               : ${DISTRIB}"
echo "CRAWLER_BUILD_ROOT_DIR: ${CRAWLER_BUILD_ROOT_DIR}"
echo "WEBMINER_ROOT_DIR     : ${WEBMINER_ROOT_DIR}"
echo "VERIQUIN_CODE_DIR     : ${VERIQUIN_CODE_DIR}"
echo "VERIQUIN_CPP_DIR      : ${VERIQUIN_CPP_DIR}"
echo "DISTRIB               : ${DISTRIB}"

echo "MINERS_INSTALL_DIR    : ${MINERS_INSTALL_DIR}"
echo "SRC_DIR_EXE           : ${SRC_DIR_EXE}"
echo "SRC_DIR_LIBS          : ${SRC_DIR_LIBS}"
echo "SRC_DATA_DIR          : ${SRC_DATA_DIR}"
echo "SRC_DIR_PHP           : ${SRC_DIR_PHP}"
echo " "
echo "DST_DIR_NAME          : ${DST_DIR_NAME}"
echo "DST_DIR               : ${DST_DIR}"
echo "DST_TAR_FILE          : ${DST_TAR_FILE}"
echo "SRC_DIR_QT            : ${SRC_DIR_QT}"

# exit 1; # FIXMENM

echo "Generating Doxygen Manual and reference"
pushd ${VERIQUIN_CPP_DIR}
doxygen phpDoxyfile > /dev/null 2>&1
popd


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
    cp -r ${SRC_DATA_DIR}/robot/* ${DST_DIR}/robot/
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

    ## --- Copy Qt libs and plugins Only needed for custom Qt builds !! ---
    ## cp -r ${SRC_DIR_QT}/plugins/ ${DST_DIR}
    ## cp ${SRC_DIR_QT}/lib/lib*.so.5 ${DST_DIR}

    # --- Copy Netscavator libraries and executables ---
    cp ${SRC_DIR_LIBS}/cpp_crawl.so ${DST_DIR}
    # ### cp ${SRC_DIR_LIBS}/libscript_embedding.so ${DST_DIR}  # TODO: Statically built now! If no problems remove this line!
    cp ${SRC_DIR_PHP}/libphp-sleipner5.so ${DST_DIR}
    cp ${SRC_DIR_EXE}/netscavator ${DST_DIR}
    cp ${SRC_DIR_EXE}/netcreator ${DST_DIR}
    cp ${SRC_DIR_EXE}/qtwebengine_devtools_resources.pak ${DST_DIR}
    cp ${SRC_DIR_EXE}/qtwebengine_resources_100p.pak ${DST_DIR}
    cp ${SRC_DIR_EXE}/qtwebengine_resources_200p.pak ${DST_DIR}
    cp ${SRC_DIR_EXE}/qtwebengine_resources.pak ${DST_DIR}

    ## Copy all dynamic dependencies of libqxcb.so # Only needed for custom Qt builds !!
    ##${VERIQUIN_CPP_DIR}/bin/copy_dependencies.sh ${DST_DIR}/plugins/platforms/libqxcb.so ${DST_DIR}

    # Copy all dynamic dependencies of minercreator
    ${VERIQUIN_CPP_DIR}/bin/copy_dependencies.sh ${SRC_DIR_EXE}/netcreator ${DST_DIR}

# --- strip files ---
    strip ${DST_DIR}/*.so
    strip ${DST_DIR}/cpp_crawl.so
    # ### strip ${DST_DIR}/libscript_embedding.so # TODO: Statically built now! If no problems remove this line!
    strip ${DST_DIR}/libphp-sleipner5.so
    strip ${DST_DIR}/netscavator
    strip ${DST_DIR}/netcreator

# --- doc ---
    cp ${VERIQUIN_CPP_DIR}/scriptcrawl/scriptcrawl.i ${DST_DIR}/doc

fi

pushd ${CRAWLER_BUILD_ROOT_DIR}
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


