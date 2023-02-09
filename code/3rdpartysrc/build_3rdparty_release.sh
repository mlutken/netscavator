#!/bin/bash

thirdparty_startup_dir=`pwd`

thirdparty_src_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# -----------------------------
# --- Detect system bitwith ---
# -----------------------------
BITWIDTH=64


LINUX_DIST="linux"
WIDTH=${BITWIDTH}
JOBS=6
COPY_BUILD=y
DO_BUILD=y
DELETE_SRC=y

# -------------------------------------
# --- Parse command line parameters ---
# -------------------------------------
for i in $*
do
	case $i in
        --jobs=*)
        JOBS=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
        ;;
    	--do-build=*)
		DO_BUILD=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
       --delete-src=*)
        DELETE_SRC=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
    	--copy-build=*)
		COPY_BUILD=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
        ;;
    	-h|--help)
		echo "Options:"
        echo "  --jobs=[6]"
        echo "    Set to number of jobs to use when compiling"
		echo " "
        echo "  --delete-src=[y]/n"
        echo "    Delete the source directory, and unpack new from tar before building"
        echo " "
		echo "  --do-build=[y]/n"
		echo "    Do the actual build"
		echo " "
		echo "  --copy-build=[y]/n"
		echo "    Copy build to --dst-dir-base"
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


echo "LINUX_DIST        : $LINUX_DIST"
echo "WIDTH             : $WIDTH"
echo "JOBS              : $JOBS"

cd ${thirdparty_src_dir}
./build_php_linux.sh --build-type=release --jobs=${JOBS} --delete-src=${DELETE_SRC} --do-build=${DO_BUILD} --copy-build=${COPY_BUILD}
cd ${thirdparty_src_dir}
./build_qscintilla_linux_system_qt.sh --build-type=release --jobs=${JOBS} --delete-src=${DELETE_SRC} --do-build=${DO_BUILD} --copy-build=${COPY_BUILD}
cd ${thirdparty_src_dir}
./build_swig_linux.sh --jobs=${JOBS} --delete-src=${DELETE_SRC} --do-build=${DO_BUILD} --copy-build=${COPY_BUILD}
cd ${thirdparty_startup_dir}
