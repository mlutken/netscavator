#!/bin/bash

#--- Config vars ---
PHP_VER="5.6.40"

REPOSITORY_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PARENT_NETSCAVATOR_DIR="$( dirname "${REPOSITORY_ROOT_DIR}" )"
CODE_BUILD_ROOT_DIR="${PARENT_NETSCAVATOR_DIR}/_build"
NETSCAVATOR_BUILD_ROOT_DIR="${CODE_BUILD_ROOT_DIR}/netscavator"

PROJECT_CODE_DIR=${REPOSITORY_ROOT_DIR}/code
PROJECT_CPP_DIR=${PROJECT_CODE_DIR}/cpp

### . ${PROJECT_CODE_DIR}/3rdpartysrc/webkit_version.env

# --- Make sure code is built ---
## bash ${REPOSITORY_ROOT_DIR}/build.sh -b=release

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

# -------------------
# --- Netscavator ---
# -------------------

SRC_DIR_MANUAL=${REPOSITORY_ROOT_DIR}/doc
SRC_DIR_EXE=${NETSCAVATOR_BUILD_ROOT_DIR}/bin
SRC_DIR_LIBS=${NETSCAVATOR_BUILD_ROOT_DIR}/bin
SRC_DIR_PHP=${PROJECT_CODE_DIR}/3rdparty/php-${PHP_VER}/linux_${BITWIDTH}_release/lib
SRC_DIR_QT=${PROJECT_CODE_DIR}/3rdparty/${WEBKIT_DIR}/linux_${BITWIDTH}_release
SRC_DIR_SCRIPTCRAWL=${PROJECT_CPP_DIR}/scriptcrawl
SRC_DATA_DIR=${PROJECT_CPP_DIR}/data

DST_BIN_DIR=/root/stage/bin

echo "DISTRIB_ID                : ${DISTRIB_ID}"
echo "DISTRIB_RELEASE           : ${DISTRIB_RELEASE}"
echo "DISTRIB                   : ${DISTRIB}"
echo "REPOSITORY_ROOT_DIR       : ${REPOSITORY_ROOT_DIR}"
echo "NETSCAVATOR_BUILD_ROOT_DIR: ${NETSCAVATOR_BUILD_ROOT_DIR}"
echo "PROJECT_CODE_DIR          : ${PROJECT_CODE_DIR}"
echo "PROJECT_CPP_DIR           : ${PROJECT_CPP_DIR}"
echo "DISTRIB                   : ${DISTRIB}"

echo "SRC_DIR_EXE               : ${SRC_DIR_EXE}"
echo "SRC_DIR_LIBS              : ${SRC_DIR_LIBS}"
echo "SRC_DATA_DIR              : ${SRC_DATA_DIR}"
echo "SRC_DIR_PHP               : ${SRC_DIR_PHP}"
echo " "
echo "DST_BIN_DIR               : ${DST_BIN_DIR}"
echo "SRC_DIR_QT                : ${SRC_DIR_QT}"

# exit 1; # FIXMENM

mkdir -p ${DST_BIN_DIR}
mkdir -p ${DST_BIN_DIR}/doc
mkdir -p ${DST_BIN_DIR}/robot
mkdir -p ${DST_BIN_DIR}/data
mkdir -p ${DST_BIN_DIR}/data/php/miner_utils
mkdir -p ${DST_BIN_DIR}/data/php/miner_templates
mkdir -p /usr/share/netscavator/doc


echo Copy Netscavator files to staging ...

cp -r ${REPOSITORY_ROOT_DIR}/doc /usr/share/netscavator/doc
cp ${SRC_DATA_DIR}/bin/linux/install-xvfb.sh ${DST_BIN_DIR}
cp -r ${SRC_DATA_DIR}/robot/* ${DST_BIN_DIR}/robot/
cp ${SRC_DATA_DIR}/config/php.ini.in ${DST_BIN_DIR}
cp ${SRC_DATA_DIR}/config/testcreator.cfg.in ${DST_BIN_DIR}
cp ${SRC_DATA_DIR}/config/minercreator.cfg.in ${DST_BIN_DIR}
cp ${SRC_DATA_DIR}/config/crawler.cfg.in ${DST_BIN_DIR}
cp ${SRC_DATA_DIR}/config/netscavator.cfg.in ${DST_BIN_DIR}
cp ${SRC_DATA_DIR}/config/netcreator.cfg.in ${DST_BIN_DIR}
cp ${SRC_DIR_SCRIPTCRAWL}/cpp_crawl/webminer.php ${DST_BIN_DIR}
cp ${SRC_DATA_DIR}/php/miner_utils/*.php ${DST_BIN_DIR}/data/php/miner_utils
cp ${SRC_DATA_DIR}/php/miner_templates/*.php ${DST_BIN_DIR}/data/php/miner_templates
cp ${SRC_DATA_DIR}/bin/linux/*.in ${DST_BIN_DIR}
cp -r ${SRC_DATA_DIR}/icons/ ${DST_BIN_DIR}/data
##find ${DST_BIN_DIR}/data -name "*.svn" | xargs rm -rf

cp ${SRC_DIR_LIBS}/cpp_crawl.php ${DST_BIN_DIR}

## --- Copy Qt libs and plugins Only needed for custom Qt builds !! ---
## cp -r ${SRC_DIR_QT}/plugins/ ${DST_BIN_DIR}
## cp ${SRC_DIR_QT}/lib/lib*.so.6 ${DST_BIN_DIR}

# --- Copy Netscavator libraries and executables ---
cp ${SRC_DIR_LIBS}/cpp_crawl.so ${DST_BIN_DIR}
# ### cp ${SRC_DIR_LIBS}/libscript_embedding.so ${DST_BIN_DIR}  # TODO: Statically built now! If no problems remove this line!
cp ${SRC_DIR_PHP}/libphp-sleipner5.so ${DST_BIN_DIR}
cp ${SRC_DIR_EXE}/netscavator ${DST_BIN_DIR}
cp ${SRC_DIR_EXE}/netcreator ${DST_BIN_DIR}
cp ${SRC_DIR_EXE}/qtwebengine_devtools_resources.pak ${DST_BIN_DIR}
cp ${SRC_DIR_EXE}/qtwebengine_resources_100p.pak ${DST_BIN_DIR}
cp ${SRC_DIR_EXE}/qtwebengine_resources_200p.pak ${DST_BIN_DIR}
cp ${SRC_DIR_EXE}/qtwebengine_resources.pak ${DST_BIN_DIR}

## Copy all dynamic dependencies of libqxcb.so # Only needed for custom Qt builds !!
##${PROJECT_CPP_DIR}/bin/copy_dependencies.sh ${DST_BIN_DIR}/plugins/platforms/libqxcb.so ${DST_BIN_DIR}

# Copy all dynamic dependencies of minercreator
${PROJECT_CPP_DIR}/bin/copy_dependencies.sh ${SRC_DIR_EXE}/netcreator ${DST_BIN_DIR}

# --- strip files ---
strip ${DST_BIN_DIR}/*.so
strip ${DST_BIN_DIR}/cpp_crawl.so
# ### strip ${DST_BIN_DIR}/libscript_embedding.so # TODO: Statically built now! If no problems remove this line!
strip ${DST_BIN_DIR}/libphp-sleipner5.so
strip ${DST_BIN_DIR}/netscavator
strip ${DST_BIN_DIR}/netcreator

# --- doc ---
cp ${PROJECT_CPP_DIR}/scriptcrawl/scriptcrawl.i ${DST_BIN_DIR}/doc


