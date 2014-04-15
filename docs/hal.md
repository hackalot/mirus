# Hardware Abstraction Layer
In order to facilitate ease of porting and cross-platformability, the Mirus microkernel is based upon a robust hardware abstraction layer, inspired by that used by the NT kernel.  The HAL in Mirus is heavily inspired by NT's HAL.  The goal of such a component is to provide a common base upon which the microkernel resets - a common API between hardware platforms.  The implementation of the HAL's backend is platform specific.  Only the chosen kernel platform's implementation of the HAL is included in kernel build.

## Kernel architectures
When a kernel architecture is supplied to the build system, the default (intel-i386) is overwritten and the proper arch is linked with the `core` component of the microkernel.  All machine-specific code resides in the `arch/<platform>/` directory.  Currently only i386 is supported, for simplicity and quick development - although the plan is to eventually replace the default with AMD64.

## Hardware namespaces
All HAL components, both inside and outside, reside in the so called "hardware namespace".  The back end of the HAL is the "hardware" espace itself, while the front-end is the "core.hardware" namespace.  The HAL is the basis for the kernel API, on which all low level operations are performed.