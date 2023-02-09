#!/bin/bash

#--- Config vars ---
PHP_VER="5.6.40"

CRAWLER_REPOSITORY_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PARENT_NETSCAVATOR_DIR="$( dirname "${CRAWLER_REPOSITORY_ROOT_DIR}" )"
CODE_BUILD_ROOT_DIR="${PARENT_NETSCAVATOR_DIR}/_build"
CRAWLER_BUILD_ROOT_DIR="${CODE_BUILD_ROOT_DIR}/crawler"

PROJECT_CODE_DIR=${CRAWLER_REPOSITORY_ROOT_DIR}/code
PROJECT_CPP_DIR=${PROJECT_CODE_DIR}/cpp

### . ${PROJECT_CODE_DIR}/3rdpartysrc/webkit_version.env

# --- Make sure code is built ---
## bash ${CRAWLER_REPOSITORY_ROOT_DIR}/build.sh -b=release


# -------------------
# --- Netscavator ---
# -------------------

SRC_DIR_MANUAL=${CRAWLER_BUILD_ROOT_DIR}/NetscavatorManual
SRC_DIR_EXE=${CRAWLER_BUILD_ROOT_DIR}/bin
SRC_DIR_LIBS=${CRAWLER_BUILD_ROOT_DIR}/bin
SRC_DIR_PHP=${PROJECT_CODE_DIR}/3rdparty/php-${PHP_VER}/linux_${BITWIDTH}_release/lib
SRC_DIR_QT=${PROJECT_CODE_DIR}/3rdparty/${WEBKIT_DIR}/linux_${BITWIDTH}_release
SRC_DIR_SCRIPTCRAWL=${PROJECT_CPP_DIR}/scriptcrawl
SRC_DATA_DIR=${PROJECT_CPP_DIR}/data

DST_DIR=/root/stage

echo "DISTRIB_ID            : ${DISTRIB_ID}"
echo "DISTRIB_RELEASE       : ${DISTRIB_RELEASE}"
echo "DISTRIB               : ${DISTRIB}"
echo "CRAWLER_BUILD_ROOT_DIR: ${CRAWLER_BUILD_ROOT_DIR}"
echo "PROJECT_CODE_DIR      : ${PROJECT_CODE_DIR}"
echo "PROJECT_CPP_DIR       : ${PROJECT_CPP_DIR}"
echo "DISTRIB               : ${DISTRIB}"

echo "SRC_DIR_EXE           : ${SRC_DIR_EXE}"
echo "SRC_DIR_LIBS          : ${SRC_DIR_LIBS}"
echo "SRC_DATA_DIR          : ${SRC_DATA_DIR}"
echo "SRC_DIR_PHP           : ${SRC_DIR_PHP}"
echo " "
echo "DST_DIR               : ${DST_DIR}"
echo "SRC_DIR_QT            : ${SRC_DIR_QT}"

# exit 1; # FIXMENM

mkdir -p ${DST_DIR}
mkdir -p ${DST_DIR}/doc
mkdir -p ${DST_DIR}/robot
mkdir -p ${DST_DIR}/data
mkdir -p ${DST_DIR}/data/php/miner_utils
mkdir -p ${DST_DIR}/data/php/miner_templates


echo Copy Netscavator files to staging ...

cp -r ${SRC_DIR_MANUAL} ${DST_DIR}
cp ${SRC_DATA_DIR}/bin/linux/install-xvfb.sh ${DST_DIR}
cp -r ${SRC_DATA_DIR}/robot/* ${DST_DIR}/robot/
cp ${SRC_DATA_DIR}/config/php.ini.in ${DST_DIR}
cp ${SRC_DATA_DIR}/config/testcreator.cfg.in ${DST_DIR}
cp ${SRC_DATA_DIR}/config/minercreator.cfg.in ${DST_DIR}
cp ${SRC_DATA_DIR}/config/crawler.cfg.in ${DST_DIR}
cp ${SRC_DATA_DIR}/config/netscavator.cfg.in ${DST_DIR}
cp ${SRC_DATA_DIR}/config/netcreator.cfg.in ${DST_DIR}
cp ${SRC_DIR_SCRIPTCRAWL}/cpp_crawl/webminer.php ${DST_DIR}
cp ${SRC_DATA_DIR}/php/miner_utils/*.php ${DST_DIR}/data/php/miner_utils
cp ${SRC_DATA_DIR}/php/miner_templates/*.php ${DST_DIR}/data/php/miner_templates
cp ${SRC_DATA_DIR}/bin/linux/*.in ${DST_DIR}
cp -r ${SRC_DATA_DIR}/icons/ ${DST_DIR}/data
##find ${DST_DIR}/data -name "*.svn" | xargs rm -rf

cp ${SRC_DIR_LIBS}/cpp_crawl.php ${DST_DIR}

## --- Copy Qt libs and plugins Only needed for custom Qt builds !! ---
## cp -r ${SRC_DIR_QT}/plugins/ ${DST_DIR}
## cp ${SRC_DIR_QT}/lib/lib*.so.6 ${DST_DIR}

# --- Copy Netscavator libraries and executables ---
cp ${SRC_DIR_LIBS}/cpp_crawl.so ${DST_DIR}
# ### cp ${SRC_DIR_LIBS}/libscript_embedding.so ${DST_DIR}  # TODO: Statically built now! If no problems remove this line!
cp ${SRC_DIR_PHP}/libphp-sleipner5.so ${DST_DIR}
cp ${SRC_DIR_EXE}/netscavator ${DST_DIR}
cp ${SRC_DIR_EXE}/netcreator ${DST_DIR}
cp ${SRC_DIR_EXE}/qtwebengine_devtools_resources.pak ${DST_DIR}
cp ${SRC_DIR_EXE}/qtwebengine_resources_100p.pak ${DST_DIR}
cp ${SRC_DIR_EXE}/qtwebengine_resources_200p.pak ${DST_DIR}
cp ${SRC_DIR_EXE}/qtwebengine_resources.pak ${DST_DIR}

## Copy all dynamic dependencies of libqxcb.so # Only needed for custom Qt builds !!
##${PROJECT_CPP_DIR}/bin/copy_dependencies.sh ${DST_DIR}/plugins/platforms/libqxcb.so ${DST_DIR}

# Copy all dynamic dependencies of minercreator
${PROJECT_CPP_DIR}/bin/copy_dependencies.sh ${SRC_DIR_EXE}/netcreator ${DST_DIR}

# --- strip files ---
strip ${DST_DIR}/*.so
strip ${DST_DIR}/cpp_crawl.so
# ### strip ${DST_DIR}/libscript_embedding.so # TODO: Statically built now! If no problems remove this line!
strip ${DST_DIR}/libphp-sleipner5.so
strip ${DST_DIR}/netscavator
strip ${DST_DIR}/netcreator

# --- doc ---
cp ${PROJECT_CPP_DIR}/scriptcrawl/scriptcrawl.i ${DST_DIR}/doc


