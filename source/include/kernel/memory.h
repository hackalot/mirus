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
// memory.h - Generic memory control functions
//

#pragma once

#include <stdint.h>
#include <stddef.h>

namespace mirus
{
    // memcpy
    unsigned char* memcpy(unsigned char* dest, 
        const unsigned char* src, 
        int count);

    unsigned short* memcpy(unsigned short* dest, 
        const unsigned short* src, 
        int count);

    unsigned int* memcpy(unsigned int* dest, 
        const unsigned int* src, 
        int count);

    void* memcpy_v(void* dest,
        void* src,
        size_t count);

    // memset
    extern "C" unsigned char* memset(unsigned char* dest, 
        unsigned char val, 
        int count);

    unsigned int* memset(unsigned int* dest, 
        unsigned int val, 
        int count);

    void memseti(uint8_t* dest, 
        uint8_t val, 
        uint32_t len);

    void memsetb(unsigned int* dest, 
        uint8_t val, 
        int count);

    void* memset_v(void* b,
        int val,
        size_t count);

    // memsetw
    unsigned short* memsetw(unsigned short* dest, 
        unsigned short val, 
        int count);
} // !namespace
