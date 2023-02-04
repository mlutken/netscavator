#!/bin/bash

# *** Get SONAME from object/so file ***
# objdump -R -x ../3rdparty/php-5.3.8/linux_64_release/lib/libphp5ts.so | grep SONAME

# --- Verision to build ---
PHP_VERSION="5.6.12"
PHP_DIR=./php-${PHP_VERSION}


# -----------------------------
# --- Detect system bitwith ---
# -----------------------------
BITWIDTH=64


LINUX_DIST="linux"
WIDTH=${BITWIDTH}
BUILD_TYPE="release"
#DST_DIR_BASE="../crawler/code/cpp/3rdparty/php-${PHP_VERSION}"
DST_DIR_BASE="../3rdparty/php-${PHP_VERSION}"
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
    	--build-type=*)
		BUILD_TYPE=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
    	--copy-build=*)
		COPY_BUILD=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
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
		echo "  --build-type=debug|[release]"
		echo "    Build debug or release version"
		echo " "
		echo "  --do-build=[y]/n"
		echo "    Do the actual build"
		echo " "
		echo "  --copy-build=[y]/n"
		echo "    Copy build to --dst-dir-base"
		echo " "
		echo "  --dst-dir-base=[relative-path-to-destination-base-dir]"
		echo "    Default is '${DST_DIR_BASE}/${LINUX_DIST}_${WIDTH}_${BUILD_TYPE}'"
		echo " "
		echo "  --width=[64]/32"
		echo "    Width of platform/system in bits. Note: should be auto detected if not specified"
		echo " "
		echo "  --dist=[linux]"
		echo "    Linux distribution name: 'linux', 'Ubuntu10.10', 'openSUSE11.3', ..."
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

if [ "debug" == ${BUILD_TYPE} ]
then
	DBG_COMMAND="--enable-debug"
fi


LEAF_DIR=${LINUX_DIST}_${WIDTH}_${BUILD_TYPE}
DST_DIR=${DST_DIR_BASE}/${LEAF_DIR}
mkdir -p ${DST_DIR}
DST_DIR_BASE_ABS=`cd $DST_DIR_BASE && pwd`
DST_DIR_ABS=`cd $DST_DIR && pwd`
# PARAMS="--prefix=${DST_DIR_ABS} --enable-maintainer-zts --disable-cgi --enable-cli --without-pear --disable-xml --without-sqlite --without-mysql --enable-embed=shared --enable-mbstring ${DBG_COMMAND}"
PARAMS="--prefix=${DST_DIR_ABS} --enable-maintainer-zts --disable-cgi --enable-cli --without-pear --disable-xml --without-mysql --enable-embed=shared --enable-mbstring ${DBG_COMMAND}"

#echo "DST_DIR_BASE: ${DST_DIR_BASE}"

echo "LINUX_DIST        : $LINUX_DIST"
echo "WIDTH             : $WIDTH"
echo "BUILD_TYPE        : $BUILD_TYPE"
echo "DST_DIR_BASE      : $DST_DIR_BASE"
echo "DST_DIR_BASE_ABS  : $DST_DIR_BASE_ABS"
echo "LEAF_DIR          : $LEAF_DIR"
echo "DST_DIR_ABS       : $DST_DIR_ABS"
echo "DBG_COMMAND       : $DBG_COMMAND"
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
    rm -rf ${PHP_DIR}
fi


if [ ! -d ${PHP_DIR} ] ;
then
	tar xjvf ${PHP_DIR}.tar.bz2
fi



if [ "y" == ${DO_BUILD} ]
then
	# ----------------------
	# --- Build the code ---
	# ----------------------
	# --with-pic
	# SDK Version see: https://developer.mozilla.org/En/Windows_SDK_versions#Windows_7_SDK

	pushd ${PHP_DIR}
     ./configure ${PARAMS}
    sed -i '' -e "s#libphp#libphp-sleipner#g" Makefile
	make -j$JOBS
	popd
fi


# Copy build to destination
if [ "y" == ${COPY_BUILD} ]
then
	pushd ${PHP_DIR}
	make install
	popd
# 	pushd ${DST_DIR_BASE_ABS}
# 	tar cjvf ${LEAF_DIR}.tar.bz2 ${LEAF_DIR}
# 	popd
fi

echo "DST_DIR		: ${DST_DIR}"
echo "DST_DIR_ABS	: ${DST_DIR_ABS}"
echo "DBG_COMMAND	: '${DBG_COMMAND}'"

##exit

# -----------
# --- Gem ---
# -----------

#    ./configure --prefix=${DST_DIR_ABS} --enable-maintainer-zts --disable-cgi --enable-cli --without-pear --disable-xml --without-sqlite --without-mysql --enable-embed=shared --enable-mbstring ${DBG_COMMAND}
    #./configure --prefix=${DST_DIR_ABS} --disable-cgi --enable-cli --without-pear --without-sqlite --without-mysql --enable-embed=static --enable-mbstring --enable-mbregex --disable-zip  ${DBG_COMMAND}


