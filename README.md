<img src="https://raw.github.com/joshbeitler/mirus/newsrc/documentation/resc/img/logo-type-black.png" width="35%" />

Mirus is a new operating system with the aim of trying out new and interesting things, in hopes to get the best combination possible. We throw all existing ideas and standards out the window (ie: POSIX, Single UNIX Specification) - and try to see what we can do better.

Mirus is designed primarily for higher-performance machines, such as workstations and gaming rigs, and to be used by those of higher technical knowledge. We also are trying to implement cluster-based computing and advanced load bearing capabilities.

### Core Features
* Powerful executable format
* Dynamic, node based filesystem
* Load bearing and cluster capabilities
* First-party bootloader
* Completely designed for AMD64 architecture
* Forward thinking design
* Resiliant driver framework
* Fast and lean microkernel
* Typical OS stuff (gdt, idt, etc.)

### Testing
We do not have bleeding-edge ISO images avalible currently.  In order to test drive Mirus, you will need to build it from the source - which is a relatively painless task.  You will want to clone and build the git tree from the `master` branch.  Full build instructions are found in the `support/building.text` file.

A build of Mirus with no additional configuration or specified tasks will generate a bootable `mirus.iso` in the `build` directory.  You can burn this to any bootable medium you see fit, or run it in a virtual machine.

After building Mirus, you may run `rake qemu` to run the freshly generated image in Qemu, provided it is installed.

### Building
We use `rake` along with a powerful framework designed to extend Rake known as [bit](https://github.com/joshbeitler/bit) to build Mirus .  As such, we would like to lay claim to the best build environment of any operating system.  Ever.  Building Mirus is dead simple, fast, and easy.  Go ahead, try it out for yourself!

```
rake configure
rake
```

### Dependencies
To build Mirus, you will need to meet the following dependencies.  If you are not sure whether they are installed on your system, `rake` will notify you on build.

* `rake`
* `ruby`
* `clang` >= 3.3
* `ld`
* `grub2`
* `yasm`
* `xorriso` >= 1.2.9

### Contributing
If you'd like to contribute, we would love you to go ahead.  Grab yourself a copy of the source, and get up close and personal with it.  It doesn't bite - trust us!  Make your changes on a seperate fork and send a pull request our way.

### Issue Tracker
If you run into issues (which we almost garentee you will), please post them on the [issue tracker](https://github.com/joshbeitler/mirus/issues).  Please tag and describe your issue in detail, and if any error codes are provided please include them.

### Getting Help
We are active on Twitter at [@mirusproject](http://twitter.com/mirusproject), as well as the IRC channel `#mirus` on `irc.freenode.net`.  The [wiki](https://github.com/joshbeitler/mirus/wiki) is an excellent place to look if you need a quick reference of Mirus.

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