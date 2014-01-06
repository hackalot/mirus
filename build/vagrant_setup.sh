#!/bin/sh

# The box we use for Vagrant runs Arch, so it is very bare bones.  The following
# are some base dependencies that will need to be installed for building.

# Set up our exotic toolchain choices
sudo pacman -S yasm
sudo pacman -S xorriso
sudo pacman -S clang

# Go go gem rangers
gem install colorize