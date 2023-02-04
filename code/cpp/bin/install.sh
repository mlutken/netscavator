#!/bin/bash 

SAVE_DIR_VERIQUIN_CPP_BIN="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
VERIQUIN_CODE_DIR="$( cd ${SAVE_DIR_VERIQUIN_CPP_BIN} && cd .. && cd .. && pwd )"
VERIQUIN_CPP_DIR="$( cd ${SAVE_DIR_VERIQUIN_CPP_BIN} && cd .. && pwd )"

SAVE_VERIQUIN_STARTUP_DIR=`pwd`
USER_HOME=`cd && pwd`

#cd ${VERIQUIN_CODE_DIR}
cd ${SAVE_DIR_VERIQUIN_CPP_BIN}
cd ..
. ./env.veriquin_cpp

##cd ${CPAF_ROOT_DIR}/bin/linux
##sh ./install.sh
##cd ${SAVE_DIR_VERIQUIN_CPP_BIN}


# --------------------------------
# --- Find bash file to modify ---
# --------------------------------
BASH_FILE=${USER_HOME}/.bashrc
if [[ ! -f ${BASH_FILE} ]]; then
	BASH_FILE=${USER_HOME}/.profile
fi
echo "BASH_FILE: $BASH_FILE"

# ----------------------------------------
# --- Install PATH and enviroment vars ---
# ----------------------------------------

# First get a copy of .bashrc with all webminer specific lines removed
cat ${BASH_FILE} | grep -v ADDED_BY_VERIQUIN_CPP_INSTALLER > new.bashrc

# Add our PATH extention line
echo 'export VERIQUIN_CODE_DIR='"${VERIQUIN_CODE_DIR}" '# ADDED_BY_VERIQUIN_CPP_INSTALLER' >> new.bashrc
echo 'export VERIQUIN_CPP_DIR='"${VERIQUIN_CPP_DIR}" '# ADDED_BY_VERIQUIN_CPP_INSTALLER' >> new.bashrc
#echo 'export PATH=${PATH}:${VERIQUIN_CPP_DIR}/bin # ADDED_BY_VERIQUIN_CPP_INSTALLER' >> new.bashrc

# overwrite original .bashrc with our new one and delete the new.bashrc
cp -f ./new.bashrc ${BASH_FILE}
rm ./new.bashrc

echo "Please run '. ${VERIQUIN_CPP_DIR}/env.veriquin_cpp' or open a new prompt before compiling veriquin cpp code"

# Build Netscavator in debug and release
cd ${VERIQUIN_CPP_DIR}
. env.veriquin_cpp
cbmake.py -C d
cbmake.py -c 1 -b debug -j 4
cbmake.py -c 1 -b release -j 4


cd ${SAVE_VERIQUIN_STARTUP_DIR}
