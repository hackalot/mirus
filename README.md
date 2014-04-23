<p align="center">
    <img src="https://raw.githubusercontent.com/joshbeitler/mirus/firefly-nova/docs/resources/mirus-circle.png" width="150px" /><br>
</p>

> Mirus is a new operating system designed for the future.  We throw all existing ideas and standards out the window and try to see what we can do better.  Our aim is to try out new and interesting things, in hopes of seeing what sticks.

## Testing [![Build Status](https://travis-ci.org/joshbeitler/mirus.svg?branch=firefly-nova)](https://travis-ci.org/joshbeitler/mirus)
We don't provide ready-made and up-to-date ISO images of Mirus often.  In order to try out the latest and greatest features, you'll need to build yourself a steaming fresh copy of Mirus.

```
$ git clone git@github.com:joshbeitler/mirus.git
$ cd mirus
$ rake
```

A build of Mirus with no additional configuration will generate a bootable disk image named `mirus.iso` in the `bin` directory. You can burn this to any bootable medium you see fit, or quickly run it in a virtual machine via `rake qemu`.

### Vagrant
You can use Vagrant to spin up a shiny VM, install the dependencies, and build all in one step. (You will, of course, need [Vagrant](http://vagrantup.com)  This is useful if you are building on a non-supported platform or want to have a clean environment.

```
$ vagrant up
$ vagrant ssh
$ cd /vagrant
$ rake
```

### Documentation
Piping-hot documentation is available for your use at no cost at all.  Kernel documentation is included in the `docs` directory of the source distribution, or online in the [docs](https://github.com/mirus/docs) project.

All documentation you could ever want is also available on the [wiki](https://github.com/joshbeitler/mirus/wiki), which is usually more up-to-date than the source docs.

### Contribute
Want to hack on Mirus? We'd love your help. Take a gander at our contributing guidelines found on the wiki or in the `CONTRIBUTING.md` file. Fork the project, make your changes, and hit us up with a pull request - its that easy!

Development is coordinated through the [mailing list](https://groups.google.com/forum/#!forum/mirus-dev), so be sure to join if you are interested in helping out.  We also have a [developer chat](https://gitter.im/mirus) where we discuss all things related to the project.

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
