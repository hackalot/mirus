#!/bin/sh

# The box we use for Vagrant runs Arch, so it is very bare bones.  The following
# are some base dependencies that will need to be installed for building.

# Box may be out of date
sudo pacman -Syy

# Set up our exotic toolchain choices
sudo pacman -S yasm --noconfirm
sudo pacman -S xorriso --noconfirm
sudo pacman -S clang --noconfirm

# Go go gem rangers
gem install colorize

# Build
rake