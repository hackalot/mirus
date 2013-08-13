<img src="https://raw.github.com/joshbeitler/mirus/master/docs/misc/newlooklogo-black.png" width="25%" />
=====
Mirus is a hobby operating system designed to be a playground for new and interesting OS theories.  It is not based on any other exsisting standards, allowing for a great deal of freedom in the development of the concepts behind it.

## Testing

### Note on Source Structure
You may notice that `readme.markdown` and `license.txt` are symbolic links to accordingly named files in the `support` directory.  In the Mirus world, to keep things clean, files such as READMEs, CONTRIBUTING, Licenses, and related files are moved into a directory called `support`.  You will notice this trend in projects related to Mirus (mirloader, mkdb, mircore, etc.), as well as a lot of applications that run on Mirus.  To not cause any confusion, we have symlinked the README and LICENSE files to the root directory.  Please note that this is not always the case, and also that the symlinks may cause troubles in web-based source viewers that do not support symbolic links.

### Dependencies
Mirus depends on `clang`, `grub2`, `xorriso`, `ld`, and `nasm` to build the kernel.

### Building
First of all, make sure that you have the most up-to-date source, via `git rebase`.  To  perform a build, simply run `make` on the source root.  The `mirus.iso` file is what you are looking for.  Additional makefile targets can be found in the `support/BUILDING` file.  To learn more about the source and how the directories are formatted, look in `support/source-overview`.

### Running
You can burn the ISO image to a disk (CD/DVD) and run it on actual hardware, or in a virtual machine.  We mainly support QEMU and VirtualBox, though most (if not all) capable virtual machines can run it.  We try to keep Mirus compatable with most up-to-date modern hardware.

### Debugging
Mirus has mouthwatering deugging capabilities to make the life of kernel developers easier.  If you build Mirus with the `make debug` target, the kernel image will be compiled with additional debugging symbols and information for `mkdb`, the Mirus kernel debugger.  You can debug Mirus with `mkdb` and `gdb`. In addition Mirus uses serial ports to provide on-the-fly debugging information (two way) when compiled with the `debug` flag.  You can view these logs with `tail -f` or a similar utility.  More information on debugging can be found on the wiki or in the `docs` directory.

### Kernel Panics
If you get a kernel panic, please post a new issue on the [issue tracker](https://github.com/joshbeitler/mirus/issues) with the error code, and preferably a stack trace/register dump.

## Getting Help
Something broke?  No problem, shit happens.

### IRC
You can hook up with us on IRC on `#mirus` on `irc.freenode.net`.

### Twitter
[@joshbeitler](http://twitter.com/joshbeitler) on Twitter.

### Reporting Issues
If you happen upon a bug, want a feature, or need even *more* help, please drop us a line on the Mirus [issue tracker](https://github.com/joshbeitler/mirus/issues).

## License

### Mirus
Mirus (and related userspace) is licensed under the Apache License, version 2, which can be found below and in the License.md file.

    Copyright 2013 Mirus Project
    
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
    
    http://www.apache.org/licenses/LICENSE-2.0
    
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

### Additional Components
Licenses for other included components and software not covered by the Apache license can be found in the License.md file.

