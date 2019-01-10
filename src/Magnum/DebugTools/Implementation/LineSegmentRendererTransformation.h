#ifndef Magnum_DebugTools_Implementation_LineSegmentRendererTransformation_h
#define Magnum_DebugTools_Implementation_LineSegmentRendererTransformation_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019
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

#include "Magnum/DimensionTraits.h"

namespace Magnum { namespace DebugTools { namespace Implementation {

CORRADE_IGNORE_DEPRECATED_PUSH
template<UnsignedInt dimensions> MatrixTypeFor<dimensions, Float> lineSegmentRendererTransformation(const VectorTypeFor<dimensions, Float>& a, const VectorTypeFor<dimensions, Float>& b) {
    auto transformation = MatrixTypeFor<dimensions, Float>::translation(a);
    transformation.right() = b - a;
    return transformation;
}
CORRADE_IGNORE_DEPRECATED_POP

}}}

#endif
