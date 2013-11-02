Filesystem Structure
====================

The core filesystem layout in Mirus is described in this document, including a filesystem tree and descriptions of each item.

```
* /                             Root directory
    * /system/                      System files
        * /core/                        Core files
        * /logs/                        All log files (system + application)
        * /bin/                         Core binaries
        * /library/                     Libraries (dynamic, static)
        * /config/                      All default configuration files)
        * /include/                     System header files
    * /archive/                     Archived/compressed snapshot storage
    * /snapshot/                    Periodic system images
    * /users/                       Contains user directories
        * /<username>/                  <username>'s user directory
            * /home/                        Home folder
            * /config/                      User specific configuration
            * /bin/                         User applications
            * /library/                     User libraries
            * /include/                     User includes
            * /mail/                        <username>'s mail
            * /public/                      Public directory
            * /source/                      Source code storage
    * /source/                      System source directory
        * /kernel/                      Kernel source
        * /os/                          Misc. OS related source code
    * /temp/                        Temporary files - wiped on reboot
    * /dev/                         Devices (VFS node)
        * /hda/                         Hard drive (hda1...hda_)
        * /screen/                      Screens (screen1...screen_)
        * /print/                       Printer (print1...print_)
```