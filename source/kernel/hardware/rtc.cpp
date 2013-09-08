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
// rtc.cpp - RTC clock implimentation
//

#include <hardware/rtc.hpp>
#include <util/ports.hpp>

using mirus::hardware::io::inb;
using mirus::hardware::io::outb;

namespace mirus
{
    namespace hardware
    {
        int century_register = 0x00;
        
        // Change this yearly
        const int CURRENT_YEAR = 2013;

        // cmos ports
        const int cmos_address = 0x70;
        const int cmos_data = 0x71;

        // d/t
        unsigned char century;
        unsigned int second;
        unsigned int minute;
        unsigned int hour;
        unsigned int day;
        unsigned int month;
        unsigned int year;

        int RTC::get_update_in_progress_flag()
        {
            outb(cmos_address, 0x0A);
            return (inb(cmos_data) & 0x80);
        }

        unsigned char RTC::get_rtc_register(int reg)
        {
            outb(cmos_address, reg);
            return inb(cmos_data);
        }

        void RTC::read_rtc()
        {
            unsigned char last_second;
            unsigned char last_minute;
            unsigned char last_hour;
            unsigned char last_day;
            unsigned char last_month;
            unsigned char last_year;
            unsigned char last_century;
            unsigned char registerB;
         
            // Note: This uses the "read registers until you get the same values twice in a row" technique
            //       to avoid getting dodgy/inconsistent values due to RTC updates
            
            // Make sure an update isn't in progress
            while (RTC::get_update_in_progress_flag());
            
            second = RTC::get_rtc_register(0x00);
            minute = RTC::get_rtc_register(0x02);
            hour = RTC::get_rtc_register(0x04);
            day = RTC::get_rtc_register(0x07);
            month = RTC::get_rtc_register(0x08);
            year = RTC::get_rtc_register(0x09);
            
            if(century_register != 0)
                century = RTC::get_rtc_register(century_register);
 
            do 
            {
                last_second = second;
                last_minute = minute;
                last_hour = hour;
                last_day = day;
                last_month = month;
                last_year = year;
                last_century = century;
                
                // Make sure an update isn't in progress
                while (RTC::get_update_in_progress_flag());

                second = RTC::get_rtc_register(0x00);
                minute = RTC::get_rtc_register(0x02);
                hour = RTC::get_rtc_register(0x04);
                day = RTC::get_rtc_register(0x07);
                month = RTC::get_rtc_register(0x08);
                year = RTC::get_rtc_register(0x09);
            
                if(century_register != 0)
                    century = RTC::get_rtc_register(century_register);

            } 
            while ((last_second != second) 
                || (last_minute != minute) 
                || (last_hour != hour) 
                || (last_day != day) 
                || (last_month != month) 
                || (last_year != year) 
                || (last_century != century));
 
            registerB = RTC::get_rtc_register(0x0B);
 
            // Convert BCD to binary values if necessary
            if (!(registerB & 0x04)) 
            {
                second = (second & 0x0F) + ((second / 16) * 10);
                minute = (minute & 0x0F) + ((minute / 16) * 10);
                hour = ((hour & 0x0F) + (((hour & 0x70) / 16) * 10)) | (hour & 0x80);
                day = (day & 0x0F) + ((day / 16) * 10);
                month = (month & 0x0F) + ((month / 16) * 10);
                year = (year & 0x0F) + ((year / 16) * 10);

                if(century_register != 0)
                    century = (century & 0x0F) + ((century / 16) * 10);
            }
 
            // Convert 12 hour clock to 24 hour clock if necessary
            if (!(registerB & 0x02) && (hour & 0x80)) 
            {
                hour = ((hour & 0x7F) + 12) % 24;
            }
 
            // Calculate the full (4-digit) year
            if(century_register != 0)
                year += century * 100;
            else
            {   
                year += (CURRENT_YEAR / 100) * 100;

                if(year < CURRENT_YEAR) 
                    year += 100;
            }
        }

        DateTime RTC::getTime()
        {
            DateTime dt;

            dt.setCentury(century);
            dt.setYear(year);
            dt.setMonth(month);
            dt.setDay(day);
            dt.setHour(hour);
            dt.setMinute(minute);
            dt.setSecond(second);

            return dt;
        }

        // DateTime
        unsigned int DateTime::getCentury()
        {
            return DateTime::_century;
        }

        unsigned int DateTime::getYear()
        {
            return DateTime::_year;
        }

        unsigned int DateTime::getMonth()
        {
            return DateTime::_month;
        }

        unsigned int DateTime::getDay()
        {
            return DateTime::_day;
        }

        unsigned int DateTime::getHour()
        {
            return DateTime::_hour;
        }

        unsigned int DateTime::getMinute()
        {
            return DateTime::_minute;
        }

        unsigned int DateTime::getSecond()
        {
            return DateTime::_second;
        }

        void DateTime::setCentury(unsigned int val)
        {
            DateTime::_century = val;
        }

        void DateTime::setYear(unsigned int val)
        {
            DateTime::_year = val;   
        }

        void DateTime::setMonth(unsigned int val)
        {
            DateTime::_month = val;      
        }

        void DateTime::setDay(unsigned int val)
        {
            DateTime::_day = val;   
        }

        void DateTime::setHour(unsigned int val)
        {
            DateTime::_hour = val;   
        }

        void DateTime::setMinute(unsigned int val)
        {
            DateTime::_minute = val;   
        }

        void DateTime::setSecond(unsigned int val)
        {
            DateTime::_second = val;   
        }

    } // !namespace
} // !namespace