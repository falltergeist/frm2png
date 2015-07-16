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
#include <algorithm>

// frm2png includes
#include "Exception.h"
#include "FalloutFile.h"

// Third party includes

namespace frm2png
{

FalloutFile::FalloutFile(const std::string& filename)
{
    _stream.open(filename, std::ios_base::in | std::ios_base::binary);
    if (!_stream.is_open())
    {
        throw Exception("FalloutFile::FalloutFile() - Can't open input file: " + filename);
    }
}

FalloutFile::~FalloutFile()
{
    _stream.close();
}

uint8_t FalloutFile::uint8()
{
    uint8_t value;
    char* buff = reinterpret_cast<char*>(&value);
    _stream.read(buff, 1);
    return value;
}


uint16_t FalloutFile::uint16()
{
    uint16_t value;
    char* buff = reinterpret_cast<char*>(&value);
    _stream.read(buff, 2);
    std::reverse(buff, buff + 2);
    return value;
}

uint32_t FalloutFile::uint32()
{
    uint32_t value;
    char* buff = reinterpret_cast<char*>(&value);
    _stream.read(buff, 4);
    std::reverse(buff, buff + 4);
    return value;
}

}
