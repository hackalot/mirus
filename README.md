# Mirus

Mirus is a new operating system with the aim of trying out new and interesting things, 
in hopes to get the best combination possible. We throw all existing ideas and 
standards out the window and try to see what we can do better.

### Features
* Dynamic, node based filesystem
* Resilient driver framework
* Fast and lean microkernel
* Modular architecture

## Testing [![Build Status](https://travis-ci.org/hackalot/mirus.png?branch=newsrc)](https://travis-ci.org/hackalot/mirus)
In order to test drive Mirus, you will need to build it from the source - which 
is a relatively painless task. You will want to clone and build from the `newsrc` 
branch.  Detailed build instruction can be found in the `BUILDING.md` file, 
including instructions for cross platform builds on OSX and Windows.
```
$ git clone git@github.com:joshbeitler/mirus.git
$ cd mirus
$ rake
```
A build of Mirus with no additional configuration or specified tasks will 
generate a bootable disk image named `mirus.iso` in the build/ directory. 
You can burn this to any bootable medium you see fit, or run it in a virtual 
machine via `rake qemu`.

### Vagrant
You can use Vagrant to spin up a shiny VM, install the dependencies, 
and build all in one step. (You will, of course, need [Vagrant](http://vagrantup.com))
```
$ vagrant up
$ vagrant ssh
```

### Dependencies
To build Mirus, you will need to meet the following dependencies. It is expected 
that binutils and other standard UNIX utilities are installed, but a few 
odities are required:

* `clang`
* `grub2`
* `yasm`
* `xorriso`
* `rake`

### Wiki
For further information about the project please read the wiki present in 
mirus/docs/wiki or check out the [online wiki](https://github.com/joshbeitler/mirus/wiki)

### Contribute
Want to hack on Mirus?  We'd love your help.  Take a gander at our [contributing guidelines](https://github.com/joshbeitler/mirus/wiki/Contributing)
found on the wiki or in the `docs/` directory.  Fork the project, make your changes,
and hit us up with a pull request - its that easy!

Development is coordinated through the [mailing list](https://groups.google.com/forum/#!forum/mirus-dev),
so be sure to join if you are interested in helping out.

### Getting Help
We are active on Twitter at [@mirusproject](http://twitter.com/mirusproject), 
as well as the IRC channel `#mirus` on `irc.freenode.net`. Detailed 
documentation can be found on the [wiki](https://github.com/joshbeitler/mirus/wiki) 
or in the docs/ directory of the source.

## License
```
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
