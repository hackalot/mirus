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

global enable_paging
enable_paging:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

global reload_cr3
reload_cr3:
    push ebp
    mov ebp, esp
    mov eax, cr3
    mov cr3, eax
    pop ebp
    ret
