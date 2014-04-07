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
// portio.h - generic port operations
//

#pragma once

class Port
{
public:
    //
    // Byte
    //
    unsigned char read_byte(unsigned short port);
    void write_byte(unsigned short port, unsigned char data);

    //
    // Short
    //
    unsigned short read_short(unsigned short port);
    void write_short(unsigned short port, unsigned short data);

    //
    // Long
    //
    unsigned long read_long(unsigned short port);
    void write_long(unsigned short port, unsigned long data);
};