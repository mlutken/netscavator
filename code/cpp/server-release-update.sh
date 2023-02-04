#!/bin/bash

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

# ------------------------------------------
# --- Source and destination directories ---
# ------------------------------------------

NETSCAVATOR_CPP_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
INSTALL_SRC_DIR=${NETSCAVATOR_CPP_DIR}/build_cbs/libs/shared/Release

THEHIVE_ROOT_DIR=$(cd .. && cd .. && cd .. && cd thehive && pwd)
THEHIVE_PHPLIB_DIR=${THEHIVE_ROOT_DIR}/phplib
INSTALL_DST_DIR=${THEHIVE_PHPLIB_DIR}/netscavator_${DISTRIB}

# echo "NETSCAVATOR_CPP_DIR : ${NETSCAVATOR_CPP_DIR}"
# echo "THEHIVE_ROOT_DIR    : ${THEHIVE_ROOT_DIR}"
# echo "THEHIVE_PHPLIB_DIR  : ${THEHIVE_PHPLIB_DIR}"
# echo "INSTALL_SRC_DIR     : ${INSTALL_SRC_DIR}"
# echo "INSTALL_DST_DIR     : ${INSTALL_DST_DIR}"
# echo "DISTRIB_ID          : ${DISTRIB_ID}"
# echo "DISTRIB_RELEASE     : ${DISTRIB_RELEASE}"
# echo "DISTRIB             : ${DISTRIB}"
# echo " "



if [ ! -d ${INSTALL_DST_DIR} ]; then
  echo "Creating : '${INSTALL_DST_DIR}'"
  mkdir -p ${INSTALL_DST_DIR}
fi

echo "Copying: netscavator_server.so  to ${INSTALL_DST_DIR}"
echo "Copying: netscavator_server.php to ${INSTALL_DST_DIR}"
cp ${INSTALL_SRC_DIR}/netscavator_server.so ${INSTALL_DST_DIR}
cp ${INSTALL_SRC_DIR}/netscavator_server.php ${INSTALL_DST_DIR}
