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
