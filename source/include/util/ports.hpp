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
// ports.hpp - IO port util functions
//

#pragma once

namespace mirus
{
    namespace hardware
    {
        namespace io
        {
            // byte
            unsigned char inb(unsigned short _port);
            void outb(unsigned short _port, unsigned char _data);

            // short
            unsigned short ins(unsigned short _port);
            void outs(unsigned short _port, unsigned short _data);

            // long
            unsigned int inl(unsigned short _port);
            void outl(unsigned short _port, unsigned int _data);

            // multiple short
            void insm(unsigned short _port, 
                unsigned char* data, 
                unsigned long size);

            void outsm(unsigned short _port, 
                unsigned char* data, 
                unsigned long size);
        } // !namespace
    } // !namespace
} // !namespace
