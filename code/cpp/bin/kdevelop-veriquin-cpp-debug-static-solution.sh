#!/bin/sh 

SAVE_DIR=`pwd`
BUILD_DIR=${VERIQUIN_CPP_DIR}/build_cbs/kdev_debug
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
cmake -D CMAKE_BUILD_TYPE:STRING=Debug -D CBS_BUILD=ON -D CBS_LIB_TYPE_TO_BUILD:STRING=STATIC -G "KDevelop3" ../..
cd ${SAVE_DIR}

