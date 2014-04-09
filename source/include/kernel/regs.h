// Copyright 2013 Mirus Project

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// regs.h - cpu register structure
//

#pragma once

namespace mirus
{
    struct regs
    {
        // pushed to the segs last
        unsigned int gs, fs, es, ds;
        
        // pushed by 'pusha'
        unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;

        // pushbyte + ecodes
        unsigned int int_no, err_code;

        // pushed by CPU automatically
        unsigned int eip, cs, eflags, useresp, ss;
    } __attribute__ ((__packed__));
} // !namespace