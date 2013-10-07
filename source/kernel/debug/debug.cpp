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
// debug.cpp - debugger
//

#include <stdafx.hpp>
#include <hardware/serial.hpp>
#include <util/string.hpp>
#include <util/printf.hpp>

namespace mirus
{
    namespace debug
    {
        int debugger::write(debug_level level,
            const char *fmt, 
            ...)
        {
            char buf[1024] = { -1 };
            va_list args;

            va_start(args, fmt);
            int out = vasprintf(buf, fmt, args);
            va_end(args);

            // Print
            if (buf[strlen(buf) - 1] == '\n') 
            {
                buf[strlen(buf) - 1] = '\0';
                hardware::serial::write(buf);
                hardware::serial::write('\n');
            } 
            else 
            {
                hardware::serial::write(buf);
            }   
            
            return out;    
        }
    } // !namespace
} // !namespace