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

#ifndef FRM2PNG_PNGWRITER_H
#define FRM2PNG_PNGWRITER_H

// C++ standard includes
#include <fstream>
#include <string>

// frm2png includes

// Third party includes
#include <png.h>

namespace frm2png
{
class PngImage;

class PngWriter
{
protected:
    std::ofstream _stream;
    png_structp _png_struct;
    png_infop _png_info;
public:
    PngWriter(const std::string& filename);
    ~PngWriter();

    void write(const PngImage& image);
    static void writeCallback(png_structp png_struct, png_bytep data, png_size_t length);
    static void flushCallback(png_structp png_ptr);
};

}
#endif // FRM2PNG_PNGWRITER_H
