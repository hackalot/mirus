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
// ramdisk.hpp - Tar ramdisk loader
//

#pragma once

namespace mirus
{
    namespace boot
    {
        //
        // tar_header_t - Defines the tar file header
        //
        class tar_header_t
        {
        public:
            char filename[100];
            char mode[8];
            char uid[8];
            char gid[8];
            char size[12];
            char mtime[12];
            char chksum[8];
            char typeflag[1];
        };

        //
        // get_size - Get size of tar file
        //
        uint32_t getsize(const char* in);

        //
        // parse_tar - Parse a tar file
        //
        void parse_tar(uint32_t address);
    } // !namespace
} // !namespace