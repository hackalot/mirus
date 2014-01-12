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
// ring_buffer.hpp - buffer data type
//

#pragma once

#include <stdafx.hpp>

namespace mirus
{
    class ring_buffer
    {
    public:
        int8_t* buffer;
        int8_t* buffer_end;
        int8_t* data_start;
        int8_t* data_end;
        int64_t count;
        int64_t size;

        void init(int64_t sz);
        void free();
        bool push(int8_t data);
        int8_t pop();
        bool full();
    };


} // !namespace