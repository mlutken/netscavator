#!/bin/bash

./code/3rdpartysrc/build_3rdparty_release.sh
popd
pushd netscavator
./cpaf/build_3rdparty_cpaf.sh
popd
pushd netscavator
./build.sh -b=release --test=n

