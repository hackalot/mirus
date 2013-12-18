### Build Configuration
In order to configure the build to specific needs, you will need to create a file called `config.rb` in the `build` directory.  An example build configuration file is located in the `docs` directory.
You can find the source for the targets in the `build/lib` directory, and in `Rakefile`, or by running `rake -T`

### Linux
Building on Linux is quite simple, all you need to do is clone the repo provided at https://github.com/joshbeitler/mirus and
take care of the dependencies (commands provided below), depending on your distro.

**Fedora**
```
# yum install yasm clang xorriso
```

**Debian/Ubuntu**
```
# apt-get install yasm clang xorriso
```

### OSX
With a bit of simple fanangaling, Mirus will build pretty nicely on OSX as well.  You will need to make sure you enter
Xcode's settings and install the command line tools.

```
# brew install yasm xorriso
```

###Special Note

if you're running Ubuntu, you may need to edit your `build/lib/tasks/iso.rb` file. If you're running on the older version of
GRUB, i.e. plain GRUB replace "$grub" to "grub-mkrescue". If you're on GRUB 2, the converse is applicable. Please do not change
the arguments, they can remain as it is.


### Build Targets
The following targets are avalible via `rake <target-name>`:
* `build_all` - Build all components
* `build_asm` - Build only assembly code components
* `build_kernel` - Build only the kernel
* `clean` - Clean up all binaries, object files, etc.
* `link` - Only perform the link stage
* `make_iso` - Create an ISO image
* `qemu` - Run in Qemu

(note, upon calling say, `make_iso` you will de facto also be calling `build_asm`, `build_kernel` and `link`
