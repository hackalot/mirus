# Building Mirus
Mirus uses `rake` to build the kernel, drivers, userspace, and other components.

## Getting Source
Source code for Mirus is hosted on [GitHub](https://github.com/joshbeitler/mirus).  It can be cloned via

```
git clone https://github.com/joshbeitler/mirus.git mirus
cd mirus
```

See the `CONTRIBUTING.md` file if you wish to submit any changes you make to the Mirus project.

## Build Targets
The following targets are avalible via `rake <target-name>`:
* `build_all` - Build all components
* `build_asm` - Build only assembly code components
* `build_kernel` - Build only the kernel
* `clean` - Clean up all binaries, object files, etc.
* `configure` - Configure your build environment to your liking
    * `configure target=targetName` - Set the name of the build target
* `link` - Only perform the link stage
* `make_iso` - Create an ISO image
* `qemu` - Run in Qemu

Note that many of these targets depend on each other.  As such, if you call, say, `make_iso`, it will also call `build_asm`, `build_kernel`, and `link`.

You can find the source for the targets in the `build/lib` directory, and in the `Rakefile`.