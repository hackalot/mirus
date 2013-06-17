<img src="https://raw.github.com/joshbeitler/mirus/master/docs/logo_tiny.png" />

[![Build Status](https://travis-ci.org/joshbeitler/mirus.png?branch=master)](https://travis-ci.org/joshbeitler/mirus)

Mirus is a hobby operating system designed to be a playground for new and interesting OS theories.  It is not based on any other exsisting standards, allowing for a great deal of freedom in the development of the concepts behind it.

## Features ##
Not much as of now...
* `printf` (so glorious...)
* GDT
* ISRs
* IDT
* memcpy and related

## Screenshots ##
<img src="https://raw.github.com/joshbeitler/mirus/master/docs/resc/screens/mirus_console.png" width="100%" />

## Testing ##
Mirus will build fine on most Unix systems that have the dependencies installed, and possibly with Mingw/Cygwin (not tested).  Normal development takes place on Fedora 18.

Once the dependencies are met, you can clone the repository with the following command:

`git clone https://github.com/joshbeitler/mirus.git`

And build with `make all`.  To generate a distribution package, perform `make dist`.

Make will build, link, and generate an ISO image of Mirus using grub2.  This can be run in your favorite VM or on physical hardware.  You can run `make kvm` to run in QEMU.  Note that we currently only officially support QEMU and VirtualBox.

## Dependencies

### Kernel
To build the Mirus kernel, you will need `nasm`, `clang`, and `GNU ld`.  In order to build the ISO image, Mirus uses the `grub2-mkrescue` utility found in the grub2 utilities collection. (Which you probably have if your system uses GRUB2)

## Resources

### Inspiration
These projects helped inspire Mirus's unique kernel architecture.

* [Plan 9 from Bell Labs](http://plan9.bell-labs.com/plan9/)
* [EROS](http://www.eros-os.org/eros.html)
* [MINIX3](http://www.minix3.org)

### References
These documents or sites helped me greatly in the development of Mirus.

* [OSDev](http://osdev.org)
* [Bran's Kernel Development Series](http://www.osdever.net/bkerndev/Docs/intro.htm)
* [James M's Kernel Tutorials](http://code.google.com/p/jamesm-tutorials/)

### Misc
Other helpful things to me.

* [とあるOS](http://torauos.org) - Helped inspire me to work on Mirus.
* [Cosmos](http://cosmos.codeplex.com) - Original stomping ground for my OS dev ventures.
* [Windows](http://toastytech.com/guis/bob.html) - For sucking so much it caused me to want to see if I could do better...

## Related Projects
These projects are directly related to Mirus.

* [Mirloader](http://github.com/joshbeitler/mirloader) - Eventual bootloader for Mirus.
* [Mirlabs](http://github.com/joshbeitler/mirlabs) - Testing grounds for a lot of Mirus' more...crazy features.

## License

### Mirus
Mirus (and related userspace) is licensed under the MIT License, found below and in the License.md file.

    The MIT License (MIT)

    Copyright (c) 2013 Joshua Beitler, Mirus contributors

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

### Additional Components
Licenses for other included components and software not covered by the MIT license can be found in the License.md file.
