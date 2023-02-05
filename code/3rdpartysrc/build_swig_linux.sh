#!/bin/bash

# *** Get SONAME from object/so file ***
# objdump -R -x ../3rdparty/swig-5.3.8/linux_64_release/lib/libswig5ts.so | grep SONAME

# NOTE: SWIG version 3.0.12 is the last to support PHP5!
# There is a branch called php8-support, which tries to use PHP8, but so far it does not compile.
# Help would be appreciated greatly :)
# --- Version to build ---
SWIG_VERSION="3.0.12"
SWIG_DIR=./swig-${SWIG_VERSION}


# -----------------------------
# --- Detect system bitwith ---
# -----------------------------
BITWIDTH=64


LINUX_DIST="linux"
WIDTH=${BITWIDTH}
DST_DIR_BASE="../3rdparty/swig-${SWIG_VERSION}"
DBG_COMMAND=""
COPY_BUILD=y
DO_BUILD=y
DELETE_SRC=y
JOBS=6

# -------------------------------------
# --- Parse command line parameters ---
# -------------------------------------
for i in $*
do
	case $i in
    	--do-build=*)
		DO_BUILD=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
    	--dst-dir-base=*)
		DST_DIR_BASE=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
    	--width=*)
		WIDTH=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
    	--dist=*)
		LINUX_DIST=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
       --delete-src=*)
        DELETE_SRC=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
        ;;
        --jobs=*)
        JOBS=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
        ;;
    	-h|--help)
		echo "Options:"
		echo "  --do-build=[y]/n"
		echo "    Do the actual build"
		echo " "
		echo "  --copy-build=[y]/n"
		echo "    Copy build to --dst-dir-base"
		echo " "
		echo "  --dst-dir-base=[relative-path-to-destination-base-dir]"
		echo "    Default is '${DST_DIR_BASE}'"
		echo " "
		echo "  --width=[64]/32"
		echo "    Width of platform/system in bits. Note: should be auto detected if not specified"
		echo " "
        echo "  --delete-src=[y]/n"
        echo "    Delete the source directory, and unpack new from tar before building"
        echo " "
        echo "  --jobs=[6]"
        echo "    Set to number of jobs to use when compiling"
        echo " "
		exit
		;;
    	--default)
		DEFAULT=YES
		;;
    	*)
                # unknown option
		;;
  	esac
done

LEAF_DIR=${LINUX_DIST}_${WIDTH}
DST_DIR=${DST_DIR_BASE}/${LEAF_DIR}
mkdir -p ${DST_DIR}
DST_DIR_BASE_ABS=`cd $DST_DIR_BASE && pwd`
DST_DIR_ABS=`cd $DST_DIR && pwd`
PARAMS="--prefix=${DST_DIR_ABS}"

#echo "DST_DIR_BASE: ${DST_DIR_BASE}"

echo "LINUX_DIST        : $LINUX_DIST"
echo "WIDTH             : $WIDTH"
echo "DST_DIR_BASE      : $DST_DIR_BASE"
echo "DST_DIR_BASE_ABS  : $DST_DIR_BASE_ABS"
echo "LEAF_DIR          : $LEAF_DIR"
echo "DST_DIR_ABS       : $DST_DIR_ABS"
echo "COPY_BUILD        : $COPY_BUILD"
echo "DO_BUILD          : $DO_BUILD "
echo "DELETE_SRC        : $DELETE_SRC"
echo "JOBS              : $JOBS"
echo "./configure ${PARAMS}"

sleep 10
#exit 0
###########


# --delete source dir if requested
if [ "y" == ${DELETE_SRC} ]
then
    echo "deleting source dir ...."
    sleep 3
    rm -rf ${SWIG_DIR}
fi


if [ ! -d ${SWIG_DIR} ] ;
then
	tar xzvf ${SWIG_DIR}.tar.gz
fi



if [ "y" == ${DO_BUILD} ]
then
	# ----------------------
	# --- Build the code ---
	# ----------------------
	# --with-pic
	# SDK Version see: https://developer.mozilla.org/En/Windows_SDK_versions#Windows_7_SDK

	pushd ${SWIG_DIR}
     ./configure ${PARAMS}
	make -j$JOBS
	popd
fi


# Copy build to destination
if [ "y" == ${COPY_BUILD} ]
then
	pushd ${SWIG_DIR}
	make install
	popd
	pushd ${DST_DIR_BASE_ABS}
fi

echo "DST_DIR		: ${DST_DIR}"
echo "DST_DIR_ABS	: ${DST_DIR_ABS}"

##exit

# in phprun.swg
# #define SWIG_fail goto fail
#
# #ifdef ZTS
#     void*** tsrm_ls;
# #endif



