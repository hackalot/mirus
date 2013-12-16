#!/bin/sh

# Set up clang development libraries
sudo apt-get install libclang-dev

# Install pip
sudo apt-get install python-pip
sudo pip install cldoc
pip install pyparsing

# install assembler
sudo apt-get install yasm

# install gems for rake
gem install colorize
