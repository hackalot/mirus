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

global tss_flush
tss_flush:
    mov ax, 0x2B
    ltr ax
    ret

global test_func
test_func:
    mov eax, 0x0
    int 0x80
    ; sti

global jmp_usermode
jmp_usermode:
    ; cli
    mov ax, 0x23
    mov cs, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push 0x23
    push eax
    pushf
    pop eax
    or eax, 0x200
    push eax
    push 0x1B
    mov eax, [esp + 20]
    push eax
    iret