#!/bin/bash

config=$1

if [ -z "$config" ]
then
    config="Debug"
fi

./build/game/$config/game
