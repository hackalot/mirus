Mirus [![Build Status](https://travis-ci.org/joshbeitler/mirus.png?branch=master)](https://travis-ci.org/joshbeitler/mirus)
=====
Mirus is a hobby operating system designed to be a playground for new and interesting OS theories.  It is not based on any other exsisting standards, allowing for a great deal of freedom in the development of the concepts behind it.

## Features ##
* The basics (gdt, irq, isrs, kprintf)

## Testing ##
Mirus will build fine on most Unix systems that have the dependencies installed, and possibly with Mingw/Cygwin (not tested).  Normal development takes place on Fedora 18.

Once the dependencies are met, you can clone the repository with the following command:

`git clone https://github.com/joshbeitler/mirus.git`

And build with `make all`.  To generate a distribution package, perform `make dist`.

Make will build, link, and generate an ISO image of Mirus using grub2.  This can be run in your favorite VM or on physical hardware.  You can run `make kvm` to run in QEMU.  Note that we currently only officially support QEMU and VirtualBox.

## Dependencies

### Kernel
To build the Mirus kernel, you will need `nasm`, `clang`, and `GNU ld`.  In order to build the ISO image, Mirus uses the `grub2-mkrescue` utility found in the grub2 utilities collection. (Which you probably have if your system uses GRUB2)

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
