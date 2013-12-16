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
// ports.cpp - IO port util functions
//

#include <util/ports.hpp>

namespace mirus
{
    namespace hardware
    {
        namespace io
        {
            unsigned char inb(unsigned short _port)
            {
                unsigned char rv;
                asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (_port));
                return rv;
            }

            void outb(unsigned short _port, unsigned char _data)
            {
                asm volatile ("outb %1, %0" : : "dN" (_port), "a" (_data));
            }

            unsigned short ins(unsigned short _port) 
            {
                unsigned short rv;
                asm volatile ("inw %1, %0" : "=a" (rv) : "dN" (_port));
                return rv;
            }

            void outs(unsigned short _port, unsigned short _data) 
            {
                asm volatile ("outw %1, %0" : : "dN" (_port), "a" (_data));
            }

            unsigned int inl(unsigned short _port) 
            {
                unsigned short rv;
                asm volatile ("inl %%dx, %%eax" : "=a" (rv) : "dN" (_port));
                return rv;
            }

            void outl(unsigned short _port, unsigned int _data) 
            {
                asm volatile ("outl %%eax, %%dx" : : "dN" (_port), "a" (_data));
            }

            void insm(unsigned short _port,
                unsigned char* data,
                unsigned long size)
            {
                asm volatile ("rep insw" : "+D" (data), "+c" (size) : "d" (_port) : "memory");
            }

            void outsm(unsigned short _port,
                unsigned char* data,
                unsigned long size)
            {
                asm volatile ("rep outsw" : "+S" (data), "+c" (size) : "d" (_port));
            }
        } // !namespace
    } // !namespace
} // !namespace