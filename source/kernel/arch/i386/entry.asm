; Copyright 2013 Mirus Project

; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at

; http://www.apache.org/licenses/LICENSE-2.0

; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.

; Declare constants used for creating a multiboot header.
MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bootstrap_stack
align 4
stack_bottom:
times 16384 db 0
stack_top:

section .text
global _start
_start:
    ; mov esp, stack_top
    mov esp, 0x7FFFF
    push esp

    ; multiboot information
    push eax
    push ebx

    extern kernel_main
    call kernel_main

    cli
.hang:
    hlt
    jmp .hang