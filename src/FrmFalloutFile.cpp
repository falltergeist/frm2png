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

// frm2png includes
#include "FrmFalloutFile.h"
#include "pallete.h"

// Third party includes

namespace frm2png
{
    FrmFalloutFile::FrmFalloutFile(const std::string& filename) : FalloutFile(filename)
    {
        _version = uint32(); // version
        _framesPerSecond = uint16(); // frames per second
        _actionFrame = uint16(); // action frame
        _framesPerDirection = uint16();

        for (unsigned i = 0; i != 6; ++i) {
            uint16(); // direction x shift
        }

        for (unsigned i = 0; i != 6; ++i) {
            uint16(); // direction y shift
        }

        uint32_t lastOffset = -1;
        for (unsigned i = 0; i != 6; ++i) {
            uint32_t offset = uint32(); // direction pixel data offset
            if (offset == lastOffset) {
                continue;
            }

            lastOffset = offset;
            _frames.insert(std::pair<uint8_t, std::vector<FrmFrame>>(i, std::vector<FrmFrame>()));
        }

        uint32(); // frm data size

        for (unsigned i = 0; i != _frames.size(); ++i) {
            for(unsigned j = 0; j != _framesPerDirection; ++j) {
                uint16_t width = uint16();
                uint16_t height = uint16();
                uint32(); // frame pixel data size
                uint16(); // x offset
                uint16(); // y offset

                FrmFrame frame(width, height);
                for(unsigned y = 0; y != frame.height(); ++y) {
                    for (unsigned int x = 0; x != frame.width(); ++x) {
                        uint8_t index = uint8();

                        if (!index) {
                            frame.setPixel(x, y, Color(0));
                            continue;
                        } else {
                            uint8_t red   = pallete.at(index).red   * _colorModifier;
                            uint8_t green = pallete.at(index).green * _colorModifier;
                            uint8_t blue  = pallete.at(index).blue  * _colorModifier;
                            frame.setPixel(x, y, Color(red, green, blue));
                        }
                    }
                }
                _frames.at(i).push_back(frame);
            }
        }
    }

    FrmFalloutFile::~FrmFalloutFile()
    {
    }

    std::map<uint8_t, std::vector<FrmFrame>>& FrmFalloutFile::frames()
    {
        return _frames;
    }

    uint16_t FrmFalloutFile::actionFrame()
    {
        return _actionFrame;
    }

    uint16_t FrmFalloutFile::framesPerDirection()
    {
        return _framesPerDirection;
    }

    uint16_t FrmFalloutFile::framesPerSecond()
    {
        return _framesPerSecond;
    }

    uint32_t FrmFalloutFile::version()
    {
        return _version;
    }
}
