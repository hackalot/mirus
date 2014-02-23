# About this branch

### Why rewrite?
Mirus is currently a mishmash of various code styles, functionality is lacking, and the project goals cannot be effectively realized in the current mess.

### How is this going to be different?
First off, the rewrite is taking place in D, due to its nicer syntax and more modern design.

Additionally, UNIX compatibility is being relegated to a simply userspace library, similarly to Cygwin - and will not be thought of until required.  One of the original goals of Mirus was to create a new and unique architecture, not be a UNIX clone.

### What is the status?
Hardly anything is done at the current point.  Here are the main priorities:
- Get a nice, solid build system until [candy](https://github.com/joshbeitler/candy) gets to a point where its useable
- Get a booting system (implies some form out terminal output)

### Goals
- Security and stability are forefront
- Speed and agility
- Functionality
- Create a system that can leverage modern hardware to its full extent

### Additional notes
- Mirus will probably be x86-64 only from now on
