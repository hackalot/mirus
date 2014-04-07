# Hardware Abstraction Layer
In order to facilitate ease of porting and cross-platformability, the Mirus microkernel is based upon a robust hardware abstraction layer, inspired by that used by the NT kernel.

## Kernel architectures
When a kernel architecture is supplied to the build system, the default (intel-i386) is overwritten and the proper arch is linked with the `core` component of the microkernel.  All machine-specific code resides in the `arch/<platform>/` directory.  Currently only i386 is supported, for simplicity and quick development - although the plan is to eventually replace the default with AMD64.

## Hardware namespace
All hardware specific functionality is wrapped into generic classes in the `mirus.core.hardware` namespace.  Kernel API equivalents for platform-specific components exist to lesson the amount of code change required for porting.  For example, an Intel i386 compatible GDT uses a lot of machine-specific code.  The HAL includes a generic GDT class that wraps the Intel GDT class (from the arc/i386/ directory) transparently.  The kernel has no knowledge that the GDT is in fact an Intel one by way of just how the GDT works.