#!/bin/bash

NETSCAVATOR_REPOSITORY_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CODE_ROOT_DIR="$( dirname "${NETSCAVATOR_REPOSITORY_ROOT_DIR}" )"
CODE_BUILD_ROOT_DIR="${CODE_ROOT_DIR}/_build"
NETSCAVATOR_BUILD_ROOT_DIR="${CODE_BUILD_ROOT_DIR}/netscavator"


REBUILD="n"
BUILD_TYPE="release"
RUN_TESTS="y"
SUGGEST_USAGE="n"

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

# echo "DISTRIB_ID                    : '${DISTRIB_ID}'"
# echo "DISTRIB_RELEASE               : '${DISTRIB_RELEASE}'"
# echo "DISTRIB                       : '${DISTRIB}'"
# echo "NETSCAVATOR_REPOSITORY_ROOT_DIR   : '${NETSCAVATOR_REPOSITORY_ROOT_DIR}'"
# echo "CODE_ROOT_DIR                 : '${CODE_ROOT_DIR}'"
# echo "CODE_BUILD_ROOT_DIR           : '${CODE_BUILD_ROOT_DIR}'"
# echo "NETSCAVATOR_BUILD_ROOT_DIR        : '${NETSCAVATOR_BUILD_ROOT_DIR}'"

# -------------------------------------
# --- Parse command line parameters ---
# -------------------------------------
for i in $*
do
	case $i in
    	-r=*|--rebuild=*)
		REBUILD=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
    	-b=*|--buildtype=*)
		BUILD_TYPE=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
    	;;
    	-t=*|--test=*)
		RUN_TESTS=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
    	;;
    	-h|--help)
		echo "Options:"
		echo "  -r=|--rebuild=[$REBUILD]"
		echo "    Rebuild all: Values 'y' OR 'n'."
		echo " "
		echo "  -b=|--buildtype=[$BUILD_TYPE]"
		echo "    'debug' or 'release' or '' (release)."
		echo " "
		echo "  -t=|--test=[$RUN_TESTS]"
		echo "    Run tests. Values 'y' or 'n'."
		echo " "
		echo "  -h=|--help"
		echo "    Print this help"
		echo " "
		exit
		;;
    	--default)
		SUGGEST_USAGE="y"
		;;
    	*)
                # unknown option
		;;
  	esac
done

if [ "y" == "${REBUILD}" ]
then
    echo "Rebuilding..."
    rm -rf ${NETSCAVATOR_BUILD_ROOT_DIR}
#     mkdir -p ${NETSCAVATOR_BUILD_ROOT_DIR}
#     pushd ${NETSCAVATOR_BUILD_ROOT_DIR}
#     cmake -D CMAKE_BUILD_TYPE:STRING=${BUILD_TYPE} ../../netscavator
#     popd
fi


if [ ! -d ${NETSCAVATOR_BUILD_ROOT_DIR} -o ! -f ${NETSCAVATOR_BUILD_ROOT_DIR}/Makefile ]
then
    echo "Creating build directory '${NETSCAVATOR_BUILD_ROOT_DIR}'"
    mkdir -p ${NETSCAVATOR_BUILD_ROOT_DIR}
    echo "Running CMake in '${NETSCAVATOR_BUILD_ROOT_DIR}'"
    pushd ${NETSCAVATOR_BUILD_ROOT_DIR}
    cmake -D CMAKE_BUILD_TYPE:STRING=${BUILD_TYPE} ../../netscavator
    popd
fi


# -----------------------
# --- Print some info ---
# -----------------------
echo "REBUILD          : '${REBUILD}'"
echo "BUILD_TYPE       : '${BUILD_TYPE}'"

pushd ${NETSCAVATOR_BUILD_ROOT_DIR}
echo "Building in: '${NETSCAVATOR_BUILD_ROOT_DIR}'"
make -j
popd

if [ "y" == "${RUN_TESTS}" ]
then
    echo "Running tests ..."
    pushd ${NETSCAVATOR_BUILD_ROOT_DIR}
    ctest
    popd
fi




