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
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

// frm2png includes
#include "Color.h"
#include "PngImage.h"
#include "PngWriter.h"
#include "pallete.h"

// Third party includes
#include <png.h>

using namespace frm2png;

uint8_t readUINT8(std::ifstream& stream)
{
    uint8_t value;
    char* buff = reinterpret_cast<char*>(&value);
    stream.read(buff, 1);
    return value;
}

uint16_t readUINT16(std::ifstream& stream)
{
    uint16_t value;
    char* buff = reinterpret_cast<char*>(&value);
    stream.read(buff, 2);
    std::reverse(buff, buff + 2);
    return value;
}

uint32_t readUINT32(std::ifstream& stream)
{
    uint32_t value;
    char* buff = reinterpret_cast<char*>(&value);
    stream.read(buff, 4);
    std::reverse(buff, buff + 4);
    return value;
}

void usage(std::string binaryName)
{
    std::cout << "FRM to PNG converter v0.0.2" << std::endl;
    std::cout << "Copyright (c) 2015 Falltergeist developers" << std::endl;
    std::cout << "Usage: " << binaryName << " <FRM filename>" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        usage(argv[0]);
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream in;

    in.open(filename.c_str(), std::ios_base::binary | std::ios_base::in);
    if (!in.is_open())
    {
        std::cout << "Can't open input file: " << filename << std::endl;
        return 1;
    }

    std::string outname = filename.substr(0, filename.find('.')) + ".png";

    readUINT32(in); // version
    readUINT16(in); // frames per second
    readUINT16(in); // action frame
    uint16_t framesPerDirection = readUINT16(in); // frames per direction

    for (unsigned i = 0; i != 6; ++i)
    {
        readUINT16(in); // direction x shift
    }

    for (unsigned i = 0; i != 6; ++i)
    {
        readUINT16(in); // direction y shift
    }

    for (unsigned i = 0; i != 6; ++i)
    {
        readUINT32(in); // direction data offset
    }

    readUINT32(in); // frm data size

// @todo: add other directions and frames
//
//    for (unsigned i = 0; i != directions; ++i)
//    {
//        for (unsigned j = 0; j != framesPerDirection; ++j)
//        {
    uint16_t frameWidth = readUINT16(in);
    uint16_t frameHeight = readUINT16(in);
    uint32_t frameDataSize = readUINT32(in);
    readUINT16(in); // x offset
    readUINT16(in); // y offset

    PngImage image(frameWidth, frameHeight);
    PngWriter writer(outname);

    //Create row data
    png_bytep* rows = new png_bytep[frameHeight];
    for(unsigned y = 0; y != frameHeight; ++y)
    {
        rows[y] = new png_byte[frameWidth*4];

        for (unsigned int x = 0; x != frameWidth; ++x)
        {
            uint8_t index = readUINT8(in);

            if (!index)
            {
                image.setPixel(x, y, Color(0));
                continue;
            }

            image.setPixel(x, y, Color(pallete.at(index).red * 4, pallete.at(index).green * 4, pallete.at(index).blue * 4));
        }
    }

    writer.write(image);


//        }
//    }





    in.close();
    return 0;
}
