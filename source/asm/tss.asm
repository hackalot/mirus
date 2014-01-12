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
    mov eax, 0
    mov ebx, 0x1
    mov ecx, 0x0
    mov edx, 0
    mov edi, 0
    mov esi, 0
    int 0x7F
    ret

global jmp_usermode
jmp_usermode:
    cli
    mov ax, 0x23   
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push 0x23      
    push esp      
    pushf      
    push 0x1b      
    lea eax, [a]      
    push eax

    iret
   a:
    add esp, 4