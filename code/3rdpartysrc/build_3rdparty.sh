#!/bin/bash

thirdparty_startup_dir=`pwd`

thirdparty_src_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd ${thirdparty_src_dir}
. important_source_me_first.env
popd

# -----------------------------
# --- Detect system bitwith ---
# -----------------------------
BITWIDTH=64


LINUX_DIST="linux"
WIDTH=${BITWIDTH}
JOBS=6

# -------------------------------------
# --- Parse command line parameters ---
# -------------------------------------
for i in $*
do
	case $i in
        --jobs=*)
        JOBS=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
        ;;
    	-h|--help)
		echo "Options:"
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


echo "LINUX_DIST        : $LINUX_DIST"
echo "WIDTH             : $WIDTH"
echo "JOBS              : $JOBS"

cd ${thirdparty_src_dir}
# ./build_swig_linux.sh --jobs=${JOBS}

./build_php_linux.sh --build-type=debug --jobs=${JOBS}
./build_php_linux.sh --build-type=release --jobs=${JOBS}

./build_qtwebkit_linux.sh --build-type=release --jobs=${JOBS}
./build_qscintilla_linux_system_qt.sh --build-type=release --jobs=${JOBS}

./build_qtwebkit_linux.sh --build-type=debug --jobs=${JOBS}
./build_qscintilla_linux_system_qt.sh --build-type=debug --jobs=${JOBS}

# For now we use htmlparser version in crawler/code/cpp/htmlparser
# ./build_htmlcxx_linux.sh --build-type=debug --jobs=${JOBS}
# ./build_htmlcxx_linux.sh --build-type=release --jobs=${JOBS}


cd ${thirdparty_startup_dir}
