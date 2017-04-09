//////////////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//
//  Copyright (c) 2017-present, Cyder.org
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in the
//  Software without restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so, subject to the
//  following conditions:
//
//      The above copyright notice and this permission notice shall be included in all
//      copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////////////////////////


#include "Bitmap.h"

namespace cyder {
    static const float DEG_TO_RAD = static_cast<float>(M_PI / 180);

    void Bitmap::render(SkCanvas* canvas) {
        this->rotation = clampRotation(this->rotation);
        float a = 1, b = 0, c = 0, d = 1, tx = 0, ty = 0;
        auto skewX = this->rotation;
        auto skewY = this->rotation;
        auto scaleX = this->scaleX;
        auto scaleY = this->scaleY;
        if ((skewX == 0) && (skewY == 0)) {
            a = scaleX;
            b = c = 0;
            d = scaleY;
        } else {
            auto u = cosf(skewX * DEG_TO_RAD);
            auto v = sinf(skewX * DEG_TO_RAD);
            if (skewX == skewY) {
                a = u * scaleX;
                b = v * scaleX;
            } else {
                a = cosf(skewY * DEG_TO_RAD) * scaleX;
                b = sinf(skewY * DEG_TO_RAD) * scaleX;
            }
            c = -v * scaleY;
            d = u * scaleY;
        }
        tx = this->x;
        ty = this->y;
        SkMatrix matrix;
        matrix.setAll(a, c, tx, b, d, ty, 0, 0, SK_Scalar1);
        canvas->setMatrix(matrix);
        SkPaint paint;
        paint.setFilterQuality(kLow_SkFilterQuality);
        canvas->drawBitmap(*bitmapData, 0, 0, &paint);
    }


    int Bitmap::clampRotation(int value) {
        value %= 360;
        if (value > 180) {
            value -= 360;
        } else if (value < -180) {
            value += 360;
        }
        return value;
    }
}

