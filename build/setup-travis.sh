#!/bin/sh

# install deps
sudo apt-get install yasm
sudo apt-get install clang
sudo apt-get install ruby2.0.0-dev

# install all the gems we need
sudo gem install colorize

gem update --system
gem --version