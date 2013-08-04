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

#ifndef _MIRUS_KERNEL_PRINTF_H_
#define _MIRUS_KERNEL_PRINTF_H_

#include <util/string.hpp>
#include <term/terminal.hpp>
#include <stdarg.h>

// TODO: replace with a more powerful varient

namespace mirus
{
    void printf(const char *args, ...);
    void printf(const int args, ...);

    void printc(char args, ...);
}

#endif
