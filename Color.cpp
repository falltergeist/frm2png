/*
 * Copyright (c) 2015 Falltergeist developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

// C++ standard includes

// frm2png includes
#include "Color.h"

// Third party includes

namespace frm2png
{

Color::Color(uint32_t rgba)
{
    _red   = ((rgba & 0xFF000000) >> 24);
    _green = ((rgba & 0x00FF0000) >> 16);
    _blue  = ((rgba & 0x0000FF00) >> 8);
    _alpha =   rgba & 0x000000FF;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _red = red;
    _green = green;
    _blue = blue;
    _alpha = alpha;
}

uint8_t Color::red() const
{
    return _red;
}

uint8_t Color::green() const
{
    return _green;
}

uint8_t Color::blue() const
{
    return _blue;
}

uint8_t Color::alpha() const
{
    return _alpha;
}

}
