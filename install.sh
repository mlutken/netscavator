#!/bin/bash 


startup_dir=`pwd`
crawler_root_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [ -d ${crawler_root_dir}/cpaf/build_cbs ];
then
    rm -rf ${crawler_root_dir}/cpaf/build_cbs
fi

echo "Running : ${crawler_root_dir}/cpaf/bin/linux/installNeededLibs_RunAsRoot.sh"
sudo ${crawler_root_dir}/cpaf/bin/linux/installNeededLibs_RunAsRoot.sh

# TODO: This step might be obsolete!
#echo "Running : ${crawler_root_dir}/cpaf/bin/linux/install.sh"
#${crawler_root_dir}/cpaf/bin/linux/install.sh


echo "Running : ${crawler_root_dir}/code/3rdpartysrc/installNeededLibs_RunAsRoot.sh"
${crawler_root_dir}/code/3rdpartysrc/installNeededLibs_RunAsRoot.sh

echo "Running : ${crawler_root_dir}/cpaf/build_3rdparty_cpaf.sh"
${crawler_root_dir}/cpaf/build_3rdparty_cpaf.sh

echo "Running : ${crawler_root_dir}/code/3rdpartysrc/build_3rdparty.sh"
${crawler_root_dir}/code/3rdpartysrc/build_3rdparty.sh


cd ${crawler_root_dir}
echo "Running : build.sh"
./build.sh

cd ${startup_dir}
