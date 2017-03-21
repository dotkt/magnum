/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <sstream>
#include <Corrade/TestSuite/Tester.h>
#include <Corrade/Utility/Directory.h>
#include <Corrade/PluginManager/Manager.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/Trade/ImageData.h>

#include "MagnumPlugins/AnyImageConverter/AnyImageConverter.h"

#include "configure.h"

namespace Magnum { namespace Trade { namespace Test {

struct AnyImageConverterTest: TestSuite::Tester {
    explicit AnyImageConverterTest();

    void png();

    void unknown();

    private:
        PluginManager::Manager<AbstractImageConverter> _manager;
};

AnyImageConverterTest::AnyImageConverterTest(): _manager{MAGNUM_PLUGINS_IMAGECONVERTER_DIR} {
    addTests({&AnyImageConverterTest::png,

              &AnyImageConverterTest::unknown});
}

namespace {
    constexpr const char Data[] = {
        1, 2, 3, 2, 3, 4, 0, 0,
        3, 4, 5, 4, 5, 6, 0, 0,
        5, 6, 7, 6, 7, 8, 0, 0
    };

    const ImageView2D Image{PixelFormat::RGB, PixelType::UnsignedByte, {2, 3}, Data};
}

void AnyImageConverterTest::png() {
    if(_manager.loadState("PngImageConverter") == PluginManager::LoadState::NotFound)
        CORRADE_SKIP("PngImageConverter plugin not found, cannot test");

    const std::string filename = Utility::Directory::join(ANYIMAGECONVERTER_TEST_DIR, "output.png");

    if(Utility::Directory::fileExists(filename))
        CORRADE_VERIFY(Utility::Directory::rm(filename));

    /* Just test that the exported file exists */
    AnyImageConverter converter{_manager};
    CORRADE_VERIFY(converter.exportToFile(Image, filename));
    CORRADE_VERIFY(Utility::Directory::fileExists(filename));
}

void AnyImageConverterTest::unknown() {
    std::ostringstream output;
    Error redirectError{&output};

    AnyImageConverter converter{_manager};
    CORRADE_VERIFY(!converter.exportToFile(Image, "image.xcf"));

    CORRADE_COMPARE(output.str(), "Trade::AnyImageConverter::exportToFile(): cannot determine type of file image.xcf\n");
}

}}}

CORRADE_TEST_MAIN(Magnum::Trade::Test::AnyImageConverterTest)
