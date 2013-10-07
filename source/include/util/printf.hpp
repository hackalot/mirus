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
// printf.hpp - printf and formatting
//

#pragma once

namespace mirus
{
   void print_dec(unsigned int value, 
        unsigned int width, 
        char* buf, 
        int* ptr);

    void print_hex(unsigned int value, 
        unsigned int width, 
        char* buf, 
        int* ptr);

    size_t vasprintf(char* buf, 
        const char* fmt, 
        va_list args);

    int kprintf(char* file,
        int line,
        const char* fmt,
        ...);

    int sprintf(char* buf,
        const char *fmt,
        ...);
} // !namespace