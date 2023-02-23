#!/bin/bash


if [ -d netscavator ]; then
    rm -rf netscavator
fi
git clone https://github.com/mlutken/netscavator.git;
pushd netscavator
pwd
git clone https://github.com/mlutken/cpaf.git;
popd
