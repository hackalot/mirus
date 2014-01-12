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
// ring_buffer.cpp - buffer data type
//

#include <ds/ring_buffer.hpp>

namespace mirus
{
    void ring_buffer::init(int64_t sz)
    {
        ring_buffer::buffer     = (int8_t*)(sizeof(int8_t) * sz);
        ring_buffer::buffer_end = ring_buffer::buffer + sz;
        ring_buffer::size       = sz;
        ring_buffer::data_start = ring_buffer::buffer;
        ring_buffer::data_end   = ring_buffer::buffer;
        ring_buffer::count      = 0;
    }

    void ring_buffer::free()
    {
        ring_buffer::buffer = 0;
    }

    bool ring_buffer::push(int8_t data)
    {
        *ring_buffer::data_end = data; //
        ring_buffer::data_end++;

        if (ring_buffer::data_end == ring_buffer::buffer_end)
            ring_buffer::data_end = ring_buffer::buffer;

        if (ring_buffer::full()) 
        {
            if ((ring_buffer::data_start + 1) == ring_buffer::buffer_end)
                ring_buffer::data_start = ring_buffer::buffer;
            else
                ring_buffer::data_start++;
        } 
        else 
        {
            ring_buffer::count++;
        }

        return true;
    }

    int8_t ring_buffer::pop()
    {
        if (ring_buffer::buffer == NULL)
            return false;

        int8_t data = *ring_buffer::data_start; //
        ring_buffer::data_start++;

        if (ring_buffer::data_start == ring_buffer::buffer_end)
            ring_buffer::data_start = ring_buffer::buffer;

        ring_buffer::count--;

        return data;
    }

    bool ring_buffer::full()
    {
        return ring_buffer::count == ring_buffer::size;
    }
} // !namespace