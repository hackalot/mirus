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
// rtc.hpp - RTC clock implimentation
//

#pragma once

namespace mirus
{
    namespace hardware
    {
        class DateTime
        {
        public:
            // Getters
            unsigned int getCentury();
            unsigned int getYear();
            unsigned int getMonth();
            unsigned int getDay();
            unsigned int getHour();
            unsigned int getMinute();
            unsigned int getSecond();

            // Setters
            void setCentury(unsigned int val);
            void setYear(unsigned int val);
            void setMonth(unsigned int val);
            void setDay(unsigned int val);
            void setHour(unsigned int val);
            void setMinute(unsigned int val);
            void setSecond(unsigned int val);

        private:
            unsigned int _century;
            unsigned int _year;
            unsigned int _month;
            unsigned int _day;
            unsigned int _hour;
            unsigned int _minute;
            unsigned int _second;
        };

        class RTC
        {
        public:
            // helper functions
            static int get_update_in_progress_flag();
            static unsigned char get_rtc_register(int reg);
            static void read_rtc();
            static DateTime getTime();
        };
    } // !namespace
} // !namespace