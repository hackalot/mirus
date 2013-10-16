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
// ramdisk.cpp - Tar ramdisk loader
//

#include <stdafx.hpp>
#include <boot/ramdisk.hpp>

namespace mirus
{
    namespace boot
    {
        //
        // headers - File headers for all our files
        //
        tar_header_t* headers[32];

        //
        // get_size - Get size of tar file
        //
        uint32_t get_size(const char* in)
        {
            uint32_t size = 0;
            uint32_t j;
            uint32_t count = 1;

            for (j = 11; j > 0; j--, count *= 8)
                size += ((in[j - 1] - '0') * count);

            return size;
        }

        //
        // parse_tar - Parse a tar file
        //
        void parse_tar(uint32_t address)
        {
            for (uint32_t i = 0; ; i++)
            {
                tar_header_t* header = (tar_header_t*)address;
                char* file_content = (((char*)address) + 512);

                if (header->filename[0] == '\0')
                    break;

                uint32_t size = get_size(header->size);

                headers[i] = header;

                ktrace(trace_level::log, "Filename: %s\n", header->filename);
                ktrace(trace_level::log, "\tFile size: %d\n", size);
                ktrace(trace_level::log, "\tFile content: %s\n", file_content);

                address += ((size / 512) + 1) * 512;

                if (size % 512)
                    address += 512;
            }
        }
    } // !namespace
} // !namespace