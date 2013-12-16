# Building Mirus
Mirus uses `rake` to build the kernel, drivers, userspace, and other components.

### Getting Source
Source code for Mirus is hosted on [GitHub](https://github.com/joshbeitler/mirus).  It can be cloned via

```
git clone https://github.com/joshbeitler/mirus.git --recursive
cd mirus
git submodule init
rake
```

See the `CONTRIBUTING.md` file if you wish to submit any changes you make to the Mirus project.

### Build Targets
The following targets are avalible via `rake <target-name>`:
* `build_all` - Build all components
* `build_asm` - Build only assembly code components
* `build_kernel` - Build only the kernel
* `clean` - Clean up all binaries, object files, etc.
* `link` - Only perform the link stage
* `make_iso` - Create an ISO image
* `qemu` - Run in Qemu

Note that many of these targets depend on each other.  As such, if you call, say, `make_iso`, it will also call `build_asm`, `build_kernel`, and `link`.

You can find the source for the targets in the `build/lib` directory, and in `Rakefile`, or by running `rake -T`

### Linux
Building on Linux is straightforward, simply clone and build, provided the dependencies are installed.  You can install
the needed dependencies with the following commands, depending on your distrobution.

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
