#!/bin/bash

premake4 gmake && make clean && make $@
