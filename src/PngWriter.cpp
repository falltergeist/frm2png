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

// C++ standard includes
#include "Exception.h"
#include "PngImage.h"
#include "PngWriter.h"

// frm2png includes

// Third party includes

namespace frm2png
{
    PngWriter::PngWriter(const std::string& filename)
    {
        _stream.open(filename, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
        if (!_stream.is_open()) {
            throw Exception("PngWriter::PngWriter() - Can't open output file:" + filename);
        }

        // Initialize write structure
        _png_struct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (_png_struct == NULL) {
            throw Exception("PngWriter::PngWriter() - Could not allocate write struct");
        }

        // Initialize info structure
        _png_info = png_create_info_struct(_png_struct);
        if (_png_info == NULL) {
            throw Exception("PngWriter::PngWriter() - Could not allocate info struct");
        }

        // Setup Exception handling
        if (setjmp(png_jmpbuf(_png_struct))) {
            throw Exception("PngWriter::PngWriter() - Error during png creation");
        }

        png_set_write_fn(_png_struct, &_stream, PngWriter::writeCallback, PngWriter::flushCallback);
    }

    PngWriter::~PngWriter()
    {
        png_destroy_write_struct(&_png_struct, &_png_info);
        _stream.close();
    }

    void PngWriter::writeCallback(png_structp  png_struct, png_bytep data, png_size_t length)
    {
        std::ofstream* stream = (std::ofstream*)png_get_io_ptr(png_struct);
        stream->write((char*)data, length);
    }

    void PngWriter::flushCallback(png_structp png_ptr)
    {
        std::ofstream *stream = (std::ofstream*)png_get_io_ptr(png_ptr); //Get pointer to ostream
        stream->flush();
    }

    void PngWriter::write(const PngImage& image)
    {
        // Write header info
        png_set_IHDR(
            _png_struct,
            _png_info,
            image.width(),
            image.height(),
            8,
            PNG_COLOR_TYPE_RGB_ALPHA,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT
        );
        png_write_info(_png_struct, _png_info);

        // Write data
        png_write_image(_png_struct, image.rows());
        // Write end
        png_write_end(_png_struct, NULL);
    }
}
