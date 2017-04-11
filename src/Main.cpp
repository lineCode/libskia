//////////////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//
//  Copyright (c) 2017-present, cyder.org
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


#include <sstream>
#include <skia.h>
#include "platform/Application.h"
#include "platform/Ticker.h"
#include "Bitmap.h"

namespace cyder {
    class Main {
    public:

        static const int TEST_SIZE = 1500;

        Main() {
            WindowInitOptions options;
            window = Window::New(options);
            window->setX(300);
            window->setY(150);
            window->setContentSize(800, 600);
            window->setTitle("HelloSkia");
            window->activate();
            setUpTest();
        }

        void setUpTest() {
            static SkBitmap bitmapData;
            decodeFile("assets/test.png", &bitmapData);
            float stageWidth = 1900;
            float stageHeight = 960;
            float x = 0;
            float y = 0;
            for (int i = 0; i < TEST_SIZE; i++) {
                auto bitmap = new Bitmap();
                bitmap->bitmapData = &bitmapData;
                bitmap->x = x + rand() % bitmapData.width();
                bitmap->y = y + rand() % bitmapData.height();
                bitmap->scaleX = bitmap->scaleY = 0.5;
                bitmap->rotation = rand() % 360;
                x += bitmapData.width();
                if (x > stageWidth) {
                    x = 0;
                    y += bitmapData.height();
                    if (y > stageHeight) {
                        y = 0;
                    }
                }
                iconList.push_back(bitmap);
            }
        }

        void update() {
            auto t = SkTime::GetMSecs();
            GPUScreen* screen = window->screen();
            screen->makeCurrent();
            SkSurface* surface = screen->surface();
            SkCanvas* canvas = surface->getCanvas();
            // Clear background
            canvas->clear(SK_ColorGRAY);
            canvas->save();

            int index = 0;
            for (auto& bitmap : iconList) {
                bitmap->rotation += ((index % 2) * 2 - 1) * 3;
                bitmap->render(canvas);
                index++;
            }

            canvas->restore();
            SkPaint paint;
            paint.setColor(SK_ColorWHITE);
            paint.setFlags(
                    SkPaint::kAntiAlias_Flag |
                    SkPaint::kSubpixelText_Flag);
            paint.setTextSize(40);
            std::stringstream ss;
            ss << "Cost: " << renderCost;
            auto text = ss.str();
            canvas->drawText(text.c_str(), text.length(), 10, 50, paint);

            screen->present();
            auto t2 = SkTime::GetMSecs();
            count++;
            if (count >= 30) {
                count = 0;
                renderCost = round((t2 - t) * 10) / 10;
            }
        }

        ~Main() {
            delete window;
        }

    private:
        std::vector<Bitmap*> iconList;
        double renderCost = 0;
        int count = 0;
        Window* window;
    };

    int Start(int argc, const char* argv[]) {
        Main main;
        Ticker::Start(std::bind(&Main::update, &main));
        Application::application->run();
        Ticker::Stop();
        return 0;
    }


}
