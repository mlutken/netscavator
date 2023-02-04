#!/bin/bash 
 
if ps ax | grep -v grep | grep "^\s*$1" > /dev/null
then
    echo "1"
else
    echo "0"
fi

