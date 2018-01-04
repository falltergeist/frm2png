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
#include <cstdint>
#include <iostream>
#include <string>

// frm2png includes
#include "Exception.h"
#include "FrmFalloutFile.h"
#include "PngImage.h"
#include "PngWriter.h"

// Third party includes
#include <png.h>

using namespace frm2png;

void usage(const std::string& binaryName)
{
    std::cout << "FRM to PNG converter v0.1.4" << std::endl;
    std::cout << "Copyright (c) 2015-2018 Falltergeist developers" << std::endl;
    std::cout << "Usage: " << binaryName << " <FRM filename>" << std::endl;
}

void frmInfo(FrmFalloutFile* frm)
{
    std::cout << "=== FRM info ===" << std::endl;
    std::cout << "Version: " << frm->version() << std::endl;
    std::cout << "Frames per second: " << frm->framesPerSecond() << std::endl;
    std::cout << "Action frame: " << frm->actionFrame() << std::endl;
    std::cout << "Frames per direction: " << frm->framesPerDirection() << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }

    std::string filename = argv[1];
    std::string outname = filename.substr(0, filename.find('.')) + ".png";

    try {
        FrmFalloutFile frm(filename);

        frmInfo(&frm);

        // find maximum width and height
        unsigned maxWidth = frm.frames().at(0).at(0).width();
        unsigned maxHeight = frm.frames().at(0).at(0).height();
        for (unsigned i = 0; i != frm.frames().size(); ++i) {
            for (unsigned j = 0; j != frm.frames().at(i).size(); ++j) {
                auto frame = frm.frames().at(i).at(j);
                if (frame.width() > maxWidth) maxWidth = frame.width();
                if (frame.height() > maxHeight) maxHeight = frame.height();
            }
        }

        PngImage image(maxWidth*frm.framesPerDirection(), maxHeight*frm.frames().size());

        for (unsigned i = 0; i != frm.frames().size(); ++i) {
            for (unsigned j = 0; j != frm.frames().at(i).size(); ++j) {
                auto frame = frm.frames().at(i).at(j);
                for (unsigned y = 0; y != frame.height(); ++y) {
                    for (unsigned x = 0; x != frame.width(); ++x) {
                        image.setPixel(maxWidth*j + x, maxHeight*i + y, frame.pixel(x, y));
                    }
                }
            }
        }

        PngWriter writer(outname);
        writer.write(image);
    } catch(Exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
