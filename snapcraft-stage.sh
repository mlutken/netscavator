#!/bin/bash

#--- Config vars ---
PHP_VER="5.6.40"

REPOSITORY_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PARENT_NETSCAVATOR_DIR="$( dirname "${REPOSITORY_ROOT_DIR}" )"
CODE_BUILD_ROOT_DIR="${PARENT_NETSCAVATOR_DIR}/_build"
BUILD_ROOT_DIR="${CODE_BUILD_ROOT_DIR}/netscavator"

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

# -----------------
# --- SRC paths ---
# -----------------
SRC_DIR_BIN=${BUILD_ROOT_DIR}/bin
SRC_DIR_LIBS=${BUILD_ROOT_DIR}/bin
SRC_DIR_SCRIPTCRAWL=${PROJECT_CPP_DIR}/scriptcrawl
SRC_DIR_MANUAL=${REPOSITORY_ROOT_DIR}/doc
SRC_PHP_SLEIPNER_SHARED_LIB=${PROJECT_CODE_DIR}/3rdparty/php-${PHP_VER}/linux_${BITWIDTH}_release/lib//libphp-sleipner5.so
## SRC_DIR_QT=${PROJECT_CODE_DIR}/3rdparty/${WEBKIT_DIR}/linux_${BITWIDTH}_release
SRC_DATA_DIR=${PROJECT_CPP_DIR}/data
SRC_PHP_DIR=${SRC_DATA_DIR}/php

SRC_NSS_LIB_DIR=/usr/lib/x86_64-linux-gnu/nss

COPY_DEPENDENCIES_SCRIPT=${PROJECT_CPP_DIR}/bin/copy_dependencies.sh
LD_LINUX_LIB_NAME=ld-linux-x86-64.so.2
# -----------------
# --- DST paths ---
# -----------------
STAGE_FS_ROOT=~/stage
DST_BIN_DIR=${STAGE_FS_ROOT}/usr/bin
DST_LIB_DIR=${STAGE_FS_ROOT}/lib/x86_64-linux-gnu
DST_NETSCAVATOR_ETC_DIR=${STAGE_FS_ROOT}/etc/netscavator
DST_ROOT_LIB64_DIR=${STAGE_FS_ROOT}/lib64
DST_NSS_LIB_DIR=${STAGE_FS_ROOT}/usr/lib/x86_64-linux-gnu/nss

DST_USR_SHARE_DIR=${STAGE_FS_ROOT}/usr/share/netscavator
DST_MANUAL_DIR=${DST_USR_SHARE_DIR}/doc
DST_PHP_DIR=${DST_USR_SHARE_DIR}/php
DST_DATA_DIR=${DST_USR_SHARE_DIR}/data
DST_ICONS_DIR=${DST_DATA_DIR}/icons



echo "REPOSITORY_ROOT_DIR           : ${REPOSITORY_ROOT_DIR}"
echo "BUILD_ROOT_DIR                : ${BUILD_ROOT_DIR}"
echo "PROJECT_CODE_DIR              : ${PROJECT_CODE_DIR}"
echo "PROJECT_CPP_DIR               : ${PROJECT_CPP_DIR}"
echo " "
echo "SRC_DIR_BIN                   : ${SRC_DIR_BIN}"
echo "SRC_DIR_LIBS                  : ${SRC_DIR_LIBS}"
echo "SRC_DIR_SCRIPTCRAWL           : ${SRC_DIR_SCRIPTCRAWL}"
echo "SRC_DIR_MANUAL                : ${SRC_DIR_MANUAL}"
echo "SRC_PHP_SLEIPNER_SHARED_LIB   : ${SRC_PHP_SLEIPNER_SHARED_LIB}"
echo "SRC_DATA_DIR                  : ${SRC_DATA_DIR}"
echo "SRC_PHP_DIR                   : ${SRC_PHP_DIR}"
echo "SRC_NSS_LIB_DIR               : ${SRC_NSS_LIB_DIR}"
echo "--------------------------------------------------- "
echo "STAGE_FS_ROOT                 : ${STAGE_FS_ROOT}"
echo "DST_BIN_DIR                   : ${DST_BIN_DIR}"
echo "DST_LIB_DIR                   : ${DST_LIB_DIR}"
echo "DST_NETSCAVATOR_ETC_DIR       : ${DST_NETSCAVATOR_ETC_DIR}"
echo "DST_ROOT_LIB64_DIR            : ${DST_ROOT_LIB64_DIR}"
echo "DST_NSS_LIB_DIR               : ${DST_NSS_LIB_DIR}"
echo "DST_USR_SHARE_DIR             : ${DST_USR_SHARE_DIR}"
echo "DST_MANUAL_DIR                : ${DST_MANUAL_DIR}"
echo "DST_PHP_DIR                   : ${DST_PHP_DIR}"
echo "DST_DATA_DIR                  : ${DST_DATA_DIR}"
echo "DST_ICONS_DIR                 : ${DST_ICONS_DIR}"
# echo "                   : ${}"


mkdir -p ${DST_BIN_DIR}
mkdir -p ${DST_LIB_DIR}
mkdir -p ${DST_NETSCAVATOR_ETC_DIR}
mkdir -p ${DST_ROOT_LIB64_DIR}
mkdir -p ${DST_NSS_LIB_DIR}
mkdir -p ${DST_USR_SHARE_DIR}
mkdir -p ${DST_MANUAL_DIR}
mkdir -p ${DST_PHP_DIR}
mkdir -p ${DST_DATA_DIR}
mkdir -p ${DST_ICONS_DIR}

echo Copy Netscavator files to staging ...

# ------------------------
# --- Copy executables ---
# ------------------------
cp ${SRC_DIR_BIN}/netscavator ${DST_BIN_DIR}
cp ${SRC_DIR_BIN}/netcreator ${DST_BIN_DIR}
cp ${SRC_DATA_DIR}/bin/linux/install-xvfb.sh ${DST_BIN_DIR}
cp ${SRC_DIR_BIN}/qtwebengine_devtools_resources.pak ${DST_BIN_DIR}
cp ${SRC_DIR_BIN}/qtwebengine_resources_100p.pak ${DST_BIN_DIR}
cp ${SRC_DIR_BIN}/qtwebengine_resources_200p.pak ${DST_BIN_DIR}
cp ${SRC_DIR_BIN}/qtwebengine_resources.pak ${DST_BIN_DIR}

# -------------------------
# --- Copy config files ---
# -------------------------
cp ${SRC_DATA_DIR}/config/php.ini.snap ${DST_NETSCAVATOR_ETC_DIR}/php.ini
cp ${SRC_DATA_DIR}/config/netscavator.cfg.snap ${DST_NETSCAVATOR_ETC_DIR}/netscavator.cfg
cp ${SRC_DATA_DIR}/config/netscavator.cfg.snap ${DST_NETSCAVATOR_ETC_DIR}/netcreator.cfg
# # cp ${SRC_DATA_DIR}/config/netscavator.cfg.snap ${DST_BIN_DIR}/netscavator.cfg
# # cp ${SRC_DATA_DIR}/config/netscavator.cfg.snap ${DST_BIN_DIR}/netcreator.cfg


# ----------------------
# --- Copy libraries ---
# ----------------------
cp ${SRC_DIR_LIBS}/cpp_crawl.so ${DST_LIB_DIR}
cp ${SRC_DIR_LIBS}/cpp_crawl.php ${DST_LIB_DIR}
cp ${SRC_PHP_SLEIPNER_SHARED_LIB} ${DST_LIB_DIR}

cp ${SRC_DIR_LIBS}/cpp_crawl.so ${DST_BIN_DIR}
cp ${SRC_DIR_LIBS}/cpp_crawl.php ${DST_BIN_DIR}
cp ${SRC_PHP_SLEIPNER_SHARED_LIB} ${DST_BIN_DIR}
${COPY_DEPENDENCIES_SCRIPT} ${SRC_DIR_BIN}/netcreator ${DST_LIB_DIR}

# Move ld-linux to /lib64
mv ${DST_LIB_DIR}/${LD_LINUX_LIB_NAME} ${DST_ROOT_LIB64_DIR}/

# Copy NSS libs
cp -r ${SRC_NSS_LIB_DIR}/* ${DST_NSS_LIB_DIR}/

# -------------------------------------
# --- Copy own manual/php etc files ---
# -------------------------------------
cp ${PROJECT_CPP_DIR}/scriptcrawl/scriptcrawl.i ${DST_MANUAL_DIR}/
cp -r ${SRC_DIR_MANUAL}/* ${DST_MANUAL_DIR}/
cp ${SRC_DIR_SCRIPTCRAWL}/cpp_crawl/webminer.php ${DST_BIN_DIR}
cp -r ${SRC_PHP_DIR}/* ${DST_PHP_DIR}/
# cp -r ${SRC_DATA_DIR}/icons/ ${DST_BIN_DIR}/data
cp -r ${SRC_DATA_DIR}/icons/* ${DST_ICONS_DIR}/

# # cp ${SRC_DATA_DIR}/php/miner_utils/*.php ${DST_BIN_DIR}/data/php/miner_utils
# # cp ${SRC_DATA_DIR}/php/miner_templates/*.php ${DST_BIN_DIR}/data/php/miner_templates


# -------------------
# --- strip files ---
# -------------------
# strip ${DST_BIN_DIR}/*.so
# strip ${DST_BIN_DIR}/cpp_crawl.so
# strip ${DST_BIN_DIR}/libphp-sleipner5.so
strip ${DST_BIN_DIR}/netscavator
strip ${DST_BIN_DIR}/netcreator



###############################
# mkdir -p ${DST_BIN_DIR}/data/php/miner_utils
# mkdir -p ${DST_BIN_DIR}/data/php/miner_templates



# cp ${SRC_DATA_DIR}/bin/linux/*.in ${DST_BIN_DIR}
##find ${DST_BIN_DIR}/data -name "*.svn" | xargs rm -rf

# # ${PROJECT_CPP_DIR}/bin/copy_dependencies.sh ${SRC_DIR_BIN}/netcreator ${DST_LIB_DIR}



## --- Copy Qt libs and plugins Only needed for custom Qt builds !! ---
## cp -r ${SRC_DIR_QT}/plugins/ ${DST_BIN_DIR}
## cp ${SRC_DIR_QT}/lib/lib*.so.6 ${DST_BIN_DIR}

# --- Copy Netscavator libraries and executables ---
# cp ${SRC_DIR_LIBS}/cpp_crawl.so ${DST_BIN_DIR}
# ### cp ${SRC_DIR_LIBS}/libscript_embedding.so ${DST_BIN_DIR}  # TODO: Statically built now! If no problems remove this line!
# # cp ${SRC_PHP_SLEIPNER_SHARED_LIB} ${DST_BIN_DIR}

## Copy all dynamic dependencies of libqxcb.so # Only needed for custom Qt builds !!
##${PROJECT_CPP_DIR}/bin/copy_dependencies.sh ${DST_BIN_DIR}/plugins/platforms/libqxcb.so ${DST_BIN_DIR}

# Copy all dynamic dependencies of minercreator
# # ${PROJECT_CPP_DIR}/bin/copy_dependencies.sh ${SRC_DIR_BIN}/netcreator ${DST_BIN_DIR}


# # --- strip files ---
# strip ${DST_BIN_DIR}/*.so
# strip ${DST_BIN_DIR}/cpp_crawl.so
# # ### strip ${DST_BIN_DIR}/libscript_embedding.so # TODO: Statically built now! If no problems remove this line!
# strip ${DST_BIN_DIR}/libphp-sleipner5.so
# strip ${DST_BIN_DIR}/netscavator
# strip ${DST_BIN_DIR}/netcreator
