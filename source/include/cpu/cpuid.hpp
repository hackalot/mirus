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

#ifndef _MIRUS_KERNEL_CPUID_H_
#define _MIRUS_KERNEL_CPUID_H_

namespace mirus
{
    class cpuid
    {
    public:
        // Vender names
        const char* VENDER_OLDAMD = "AMDisbetter!";
        const char* VENDER_AMD = "AuthenticAMD";
        const char* VENDER_INTEL = "GenuineIntel";
        const char* VENDER_VIA = "CentaurHauls";
        const char* VENDER_OLDTRANSMETA = "TransmetaCPU";
        const char* VENDER_TRANSMETA = "GenuineTMx86";
        const char* VENDER_CYRIX = "CyrixInstead";
        const char* VENDER_CENTAUR = "CentaurHauls";
        const char* VENDER_NEXTGEN = "NextGenDriven";
        const char* VENDER_UMC = "UMC UMC UMC";
        const char* VENDER_SIS = "SiS SiS SiS";
        const char* VENDER_NSC = "Geode by NSC";
        const char* VENDER_RISE = "RiseRiseRise";
    };
}

#endif
