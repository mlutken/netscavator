#!/bin/bash

# *** Get SONAME from object/so file ***
# objdump -R -x ../3rdparty/QScintilla-gpl-5.3.8/linux_64_release/lib/libphp5ts.so | grep SONAME
# https://www.riverbankcomputing.com/software/qscintilla/download
# Build: https://www.riverbankcomputing.com/static/Docs/QScintilla/
# Source WEBKIT_VERSION information
. webkit_version.env

# --- Version to build ---
QSCI_VERSION="2.13.3"
QSCI_DIR=./QScintilla_src-${QSCI_VERSION}



# -----------------------------
# --- Detect system bitwith ---
# -----------------------------

WIDTH=64
BUILD_TYPE="release"
LINUX_DIST="linux"
DO_BUILD=y
COPY_BUILD=y
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
    	--do-build=*)
		DO_BUILD=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
    	--copy-build=*)
		COPY_BUILD=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
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

####WEBKIT_INSTALL_DIR_BASE="../3rdparty/webkit"


WEBKIT_LEAF_DIR=${LINUX_DIST}_${WIDTH}_${BUILD_TYPE}
mkdir -p $WEBKIT_INSTALL_DIR_BASE/$WEBKIT_LEAF_DIR


WEBKIT_INSTALL_DIR_BASE_ABS=`cd $WEBKIT_INSTALL_DIR_BASE && pwd`
INSTALL_DIR=`cd ${WEBKIT_INSTALL_DIR_BASE}/${WEBKIT_LEAF_DIR} && pwd`
WHICH_QMAKE=`which qmake`

echo "LINUX_DIST        : $LINUX_DIST"
echo "COPY_BUILD        : $COPY_BUILD"
echo "DO_BUILD          : $DO_BUILD "
echo "DELETE_SRC        : $DELETE_SRC"
echo "JOBS              : $JOBS"
echo "QSCI_DIR          : $QSCI_DIR"
echo "INSTALL_DIR       : $INSTALL_DIR"
echo "WEBKIT_INSTALL_DIR_BASE       : $WEBKIT_INSTALL_DIR_BASE"
echo "WEBKIT_INSTALL_DIR_BASE_ABS: $WEBKIT_INSTALL_DIR_BASE_ABS"
echo "WEBKIT_LEAF_DIR       : $WEBKIT_LEAF_DIR"
echo "WHICH_QMAKE       : $WHICH_QMAKE"

#


sleep 5
# exit 0
###########


# *** --delete source dir if requested ***
if [ "y" == ${DELETE_SRC} ]
then
    echo "deleting source dir ...."
    sleep 3
    rm -rf ${QSCI_DIR}
fi


if [ ! -d ${QSCI_DIR} ] ;
then
	tar xzvf ${QSCI_DIR}.tar.gz
 	cp qscintilla${QSCI_VERSION}-linux.pro ${QSCI_DIR}/src/qscintilla.pro
fi



if [ "y" == ${DO_BUILD} ]
then
	# ----------------------
	# --- Build the code ---
	# ----------------------

	pushd ${QSCI_DIR}/src
    qmake6 qscintilla.pro
    make -j $JOBS
	popd
fi


# Copy build to destination
if [ "y" == ${COPY_BUILD} ]
then
	pushd ${QSCI_DIR}/src
	mkdir -p ${INSTALL_DIR}/include
	mkdir -p ${INSTALL_DIR}/lib/x86_64-linux-gnu
	cp -r Qsci ${INSTALL_DIR}/include
	cp -r libqscintilla2.a ${INSTALL_DIR}/lib/x86_64-linux-gnu
  	popd

	pushd ${WEBKIT_INSTALL_DIR_BASE_ABS}
 	tar cjvf ${WEBKIT_LEAF_DIR}.tar.bz2 ${WEBKIT_LEAF_DIR}
	popd

fi



