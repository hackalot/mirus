# Mirus
Mirus is designed for scalability and distributed systems.  Using built in protocols and features such as Harmony and `rcx`, Mirus allows for technical prowess and networking abilities unmatched by anything you've ever seen.

### Features
* Dynamic, node based filesystem
* Resilient driver framework
* Fast and lean microkernel
* Modular architecture

## Testing [![Build Status](https://travis-ci.org/joshbeitler/mirus.png?branch=newsrc)](https://travis-ci.org/joshbeitler/mirus)
In order to test drive Mirus, you will need to build it from the source - which is a relatively painless task. You will want to clone and build from the `newsrc` branch.  Detailed build instruction can be
found in the `BUILDING.md` file, including instructions for cross platform builds on OSX and Windows.
```
git clone git@github.com:joshbeitler/mirus.git
cd mirus
rake
```
A build of Mirus with no additional configuration or specified tasks will generate a bootable disk image named `mirus.iso` in the build/ directory. You can burn this to any bootable medium you see fit, or run it in a virtual machine via `rake qemu`.

### Dependencies
To build Mirus, you will need to meet the following dependencies. It is expected that binutils and other standard UNIX utilities are installed, but a few odities are required:

* `clang`
* `grub2`
* `yasm`
* `xorriso`
* `rake

### Issue Tracker
If you run into issues (which we almost guarantee you will), please post them on the [issue tracker](https://github.com/joshbeitler/mirus/issues). Please tag and describe your issue in detail, and if any error codes are provided please include them.

### Getting Help
We are active on Twitter at [@mirusproject](http://twitter.com/mirusproject), as well as the IRC channel `#mirus` on `irc.freenode.net`. You can also find us and discuss stuff on our [Community Page](https://plus.google.com/u/0/communities/100653275968141806445). Detailed documentation can be found on the [wiki](https://github.com/joshbeitler/mirus/wiki) or in the docs/ directory of the source.
