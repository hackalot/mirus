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

#ifndef _MIRUS_KERNEL_MX_H_
#define _MIRUS_KERNEL_MX_H_

namespace mirus
{
    // defines flags for the "flags" variable in the header
    enum class mx_flags : int
    {
        PLATFORM_AMD_ONLY    // AMD x64 only
    };

    // defines mx versions
    enum class mx_version : unsigned char
    {
        MX_0,               // MX 0 = development version
        MX_1                // MX 1 = production version
    };

    // defines a mirus executable file header
    class mx_header
    {
    public:
        // basic executable stuff
        unsigned char       magicnumber;
        mx_version          version;
        unsigned char       flags;

        // where do the sections start
        unsigned short      section_start_data;
        unsigned short      section_start_bss;
        unsigned short      section_start_text;

        // misc information about the app
        char*               program_name;
        char*               developer;
        
        // app version - we try to follow semver (semver.org)
        int                 version_major;
        int                 version_minor;
        int                 version_rev;
        int                 version_build;
    };

    // defines a mirus executable
    class mx
    {
    public:
        mx_header header;
    };
}

#endif
