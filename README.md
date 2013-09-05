<img src="http://i.imgur.com/Ob9C68n.png" width="15%" />

Mirus is a new operating system with the aim of trying out new and interesting things, in hopes to get the best combination possible. We throw all existing ideas and standards out the window (ie: POSIX, Single UNIX Specification) - and try to see what we can do better.

Mirus is designed primarily for higher-performance machines, such as workstations and gaming rigs, and to be used by those of higher technical knowledge. We also are trying to implement cluster-based computing and advanced load bearing capabilities.

### Core Features
* Powerful executable format
* Dynamic, node based filesystem
* Homegrown bootloader
* Completely designed for AMD64 architecture
* Forward thinking design
* Resilient driver framework
* Fast and lean microkernel
* Typical OS stuff (gdt, idt, etc.)

Please note that not all of these features are implemented yet.

### Testing
We do not have bleeding-edge ISO images available currently.  In order to test drive Mirus, you will need to build it from the source - which is a relatively painless task.  You will want to clone and build the git tree from the `master` branch.  Full build instructions are found in the `support/building.text` file.

You can run the following commands to configure and build the system:

```
rake configure
rake
```

A build of Mirus with no additional configuration or specified tasks will generate a bootable `mirus.iso` in the `build` directory.  You can burn this to any bootable medium you see fit, or run it in a virtual machine via `rake qemu`. 

### Dependencies
To build Mirus, you will need to meet the following dependencies.  If you are not sure whether they are installed on your system, `rake` will notify you on build.

**Kernel**
* `clang` >= 3.3
* `ld`
* `grub2`
* `yasm`
* `xorriso` >= 1.2.9

**Build System**
* `rake`
* `ruby`
* `colorize`
* `artii`

### Contributing
If you'd like to contribute, we would love you to go ahead.  Grab yourself a copy of the source, and get up close and personal with it.  It doesn't bite - trust us!  Make your changes on a separate fork and send a pull request our way.  See the `CONTRIBUTING.md` file for more details.

### Issue Tracker
If you run into issues (which we almost guarantee you will), please post them on the [issue tracker](https://github.com/joshbeitler/mirus/issues).  Please tag and describe your issue in detail, and if any error codes are provided please include them.

### Getting Help
We are active on Twitter at [@mirusproject](http://twitter.com/mirusproject), as well as the IRC channel `#mirus` on `irc.freenode.net`.  The [wiki](https://github.com/joshbeitler/mirus/wiki) is an excellent place to look if you need a quick reference of Mirus.

### Project Links
* [Twitter](https://twitter.com/mirusproject)
* [Ohloh](https://www.ohloh.net/p/mirus)

### License
```
Copyright 2013 Joshua Beitler

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
