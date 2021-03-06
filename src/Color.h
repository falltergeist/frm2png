/*
 * Copyright (c) 2015-2018 Falltergeist developers
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

#ifndef FRM2PNG_COLOR_H
#define FRM2PNG_COLOR_H

// C++ standard includes
#include <cstdint>

// frm2png includes

// Third party includes

namespace frm2png
{
    class Color
    {
        public:
            Color(uint32_t rgba);
            Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
            Color(const Color& other);

            uint8_t red() const;
            uint8_t green() const;
            uint8_t blue() const;
            uint8_t alpha() const;

        protected:
            uint8_t _red = 0;
            uint8_t _green = 0;
            uint8_t _blue = 0;
            uint8_t _alpha = 0;
    };
}
#endif // FRM2PNG_COLOR_H
