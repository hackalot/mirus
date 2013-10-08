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
// process.hpp - process information
//

#pragma once

namespace mirus
{
    namespace system
    {
        //
        // pid_t - helpful wrapper for process ids
        //
        typedef uint32_t pid_t;

        //
        // process_t - defines a process
        //
        class process_t
        {
        public:
            pid_t process_id;
        };
    } // !namespace
} // !namespace