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

#include <util/debug.hpp>

void mirus::debugger::write(const char *str)
{
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++)
    {
        mirus::write_serial(str[i]);
    }
}

void mirus::debugger::write(char chr)
{
    mirus::write_serial(chr);
}

void mirus::debugger::write(int wint)
{
    char *num = iota(wint);
    mirus::debugger::write(num);
}

void mirus::debugger::writeln(const char *str)
{
    mirus::debugger::write(str + '\n');
}

void mirus::debugger::flush()
{
    mirus::write_serial('\r');
}
