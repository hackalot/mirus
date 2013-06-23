#!/bin/bash
# mirus build script - pulls all the pieces together

# check dependencies
python depends.py

# do make
make clean && make debug
