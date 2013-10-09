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
// irq.hpp - IRQ implimentation
//

#pragma once

namespace mirus
{
    namespace cpu
    {
        //
        // Defines and IRQ handler
        //
        typedef void (*irq_handler_t) (struct regs *);

        //
        // irq handlers - uses C style linkage to help name mangling
        //
        extern "C"
        {
            void irq0();
            void irq1();
            void irq2();
            void irq3();
            void irq4();
            void irq5();
            void irq6();
            void irq7();
            void irq8();
            void irq9();
            void irq10();
            void irq11();
            void irq12();
            void irq13();
            void irq14();
            void irq15();
        }

        //
        // irq functions
        //
        class irq
        {
            public:
                //
                // Set up a listener
                //
                static void install_handler(int irq, 
                    irq_handler_t handler);
                
                //
                // remove a handler on an irq
                //
                static void uninstall_handler(int irq);

                //
                // remap IRQs to avoid conflicts
                //
                static void remap();

                //
                // set IRQ gates
                //
                static void gates();

                //
                // install the irq handler
                //
                static void install();

                static void ack(int irq_no);
        };

        //
        // our irq handler
        //
        extern "C" void irq_handler(struct regs* r);
    } // !namespace
} // !namespace