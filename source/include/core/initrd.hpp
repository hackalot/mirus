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
// initrd.hpp - initrd fs
//

#pragma once

namespace mirus
{
    namespace core
    {
        class ramdisk_header_t
        {
        public:
            uint8_t magic;
            uint32_t length;
            uint32_t offset;
            char name[256];
        };
    } // !namespace
} // !namespace