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
// screen.h - i386 screen drawing functions
//

#pragma once

namespace mirus
{
    //
    // Represents all usable VGA colors
    //
    enum class Color : unsigned char
    {
        Black        = 0,
        Blue         = 1,
        Green        = 2,
        Cyan         = 3,
        Red          = 4,
        Magenta      = 5,
        Brown        = 6,
        LightGrey    = 7,
        DarkGrey     = 8,
        LightBlue    = 9,
        LightGreen   = 10,
        LightCyan    = 11,
        LightRed     = 12,
        LightMagenta = 13,
        LightBrown   = 14,
        White        = 15
    };

    //
    // Returns a bg/fg combination
    //
    unsigned char make_color(unsigned char fg, unsigned char bg);

    //
    // Terminal control functions
    //
    void move_cursor();
} // !namespace