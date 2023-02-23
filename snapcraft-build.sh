#!/bin/bash

./code/3rdpartysrc/build_3rdparty_release.sh
./cpaf/build_3rdparty_cpaf.sh
./build.sh -b=release --test=n
