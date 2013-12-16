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
// trace.cpp - trace debugger functions
//

#include <stdafx.hpp>
#include <util/trace.hpp>
#include <hardware/serial.hpp>

namespace mirus
{
    //
    // trace - send a trace message
    //
    void trace(trace_level level, const char *fmt, ...)
    {
        // TODO: impliment tracing to the filesystem
    }

    static void write_level(trace_level level)
    {
        switch (level)
        {
            case trace_level::emerg:
                hardware::serial::write("[emerg ] ");
                break;
            case trace_level::alert:
                hardware::serial::write("[alert ] ");
                break;
            case trace_level::crit:
                hardware::serial::write("[crit  ] ");
                break;
            case trace_level::error:
                hardware::serial::write("[error ] ");
                break;
            case trace_level::notice:
                hardware::serial::write("[notice] ");
                break;
            case trace_level::info:
            case trace_level::msg:
            case trace_level::warn:
                hardware::serial::write("[info  ] ");
                break;
            case trace_level::none:
                break;
        }
    }

    //
    // ktrace - kernel tracing (to the debug console)
    //
    int ktrace(trace_level level, const char* fmt, ...)
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

            write_level(level);
            hardware::serial::write(buf);
            hardware::serial::write('\n');
        } 
        else 
        {
            write_level(level);
            hardware::serial::write(buf);
        }       

        return out;    
    }
} // !namespace