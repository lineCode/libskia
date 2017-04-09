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


#ifndef HELLOSKIA_BITMAP_H
#define HELLOSKIA_BITMAP_H

#include <skia.h>

namespace cyder {

    class Bitmap {
    public:
        float x = 0;
        float y = 0;
        float scaleX = 0;
        float scaleY = 0;
        int rotation = 0;
        SkBitmap* bitmapData = nullptr;

        void render(SkCanvas* canvas);

    private:
        int clampRotation(int value);
    };


    inline bool decodeFile(const char* filename, SkBitmap* bitmap,
                           SkColorType colorType = kN32_SkColorType, bool requireUnpremul = false) {
        SkASSERT(kIndex_8_SkColorType != colorType);
        sk_sp<SkData> data(SkData::MakeFromFileName(filename));
        std::unique_ptr<SkCodec> codec(SkCodec::NewFromData(data));
        if (!codec) {
            return false;
        }

        SkImageInfo info = codec->getInfo().makeColorType(colorType);
        info = info.makeAlphaType(kPremul_SkAlphaType);
        if (requireUnpremul && kPremul_SkAlphaType == info.alphaType()) {
            info = info.makeAlphaType(kUnpremul_SkAlphaType);
        }

        if (!bitmap->tryAllocPixels(info)) {
            return false;
        }

        return SkCodec::kSuccess == codec->getPixels(info, bitmap->getPixels(), bitmap->rowBytes());
    }


}
#endif //HELLOSKIA_BITMAP_H
