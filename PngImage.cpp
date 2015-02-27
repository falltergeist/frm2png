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
#include "PngImage.h"

// Third party includes

namespace frm2png
{

PngImage::PngImage(unsigned width, unsigned height)
{
    _width = width;
    _height = height;

    _rows = new png_bytep[_height]();

    for(unsigned y = 0; y != _height; ++y)
    {
        _rows[y] = new png_byte[_width*4]();
    }
}

PngImage::~PngImage()
{
    for(unsigned y = 0; y != _height; ++y)
    {
        delete [] _rows[y];
    }
    delete [] _rows;
}

void PngImage::setPixel(unsigned x, unsigned y, const Color& color)
{
    if (x >= _width || y >= _height) return;

    _rows[y][x*4] = color.red();
    _rows[y][x*4 + 1] = color.green();
    _rows[y][x*4 + 2] = color.blue();
    _rows[y][x*4 + 3] = color.alpha();
}

unsigned PngImage::width() const
{
    return _width;
}

unsigned PngImage::height() const
{
    return _height;
}

png_bytep* PngImage::rows() const
{
    return _rows;
}

}
