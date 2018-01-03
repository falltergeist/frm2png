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

#ifndef FRM2PNG_FRMFRAME_H
#define FRM2PNG_FRMFRAME_H

// C++ standard includes
#include <vector>

// frm2png includes
#include "Color.h"

// Third party includes

namespace frm2png
{
    class FrmFrame
    {
        public:
            FrmFrame(unsigned width, unsigned height);
            FrmFrame(const FrmFrame& other);
            ~FrmFrame();

            Color pixel(unsigned x, unsigned y) const;
            void setPixel(unsigned x, unsigned y, const Color& color);

            unsigned width();
            unsigned height();

        protected:
            unsigned _width;
            unsigned _height;
            std::vector<Color> _pixels;
    };
}
#endif // FRM2PNG_FRMFRAME_H
