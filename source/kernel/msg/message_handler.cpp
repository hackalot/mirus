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
// message_handler.cpp - handles the message queue
//

#include <msg/message_handler.hpp>

namespace mirus
{
    namespace system
    {
        void message_handler::dispatch_message(const message_t& msg)
        {
            // Here's how I plan to do things:
            //
            //      process_manager.get_from_pid(msg.pid_dest).messages.insert(msg)
            // 
            // Sort of
        }
    } // !namespace
} // !namespace
