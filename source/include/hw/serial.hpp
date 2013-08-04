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

#ifndef _MIRUS_KERNEL_SERIAL_H_
#define _MIRUS_KERNEL_SERIAL_H_

#include <core/ioport.hpp>

#define PORT 0x3f8  // com1

// TODO: move under a hw::serialport class
// TODO: allow specification of any serial port,
// not just COM1

namespace mirus
{
    // install the serial ports
    void serial_install();

    // triggered when we recieve input from the port
    int serial_received();
    
    // read from the serial
    char read_serial();
    
    // check if we should read anything
    int is_transmit_empty();
    
    // write to a serial port
    void write_serial(char a);
}

#endif
