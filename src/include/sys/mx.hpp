// Copyright (c) 2013 Joshua Beitler, Mirus contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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
        MX_1                // MX 1 = first version
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
