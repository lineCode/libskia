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

#ifndef HELLOSKIA_WINDOWTYPE_H
#define HELLOSKIA_WINDOWTYPE_H

#include <string>

namespace cyder {

    /**
     * The WindowType class defines constants for the type property of the WindowInitOptions object used to create a native window.
     * Note: The type value is specified when a window is created and cannot be changed.
     */
    class WindowType {
    public:
        /**
         * A typical window.
         */
        static const int NORMAL = 1;

        /**
         * A utility window.
         */
        static const int UTILITY = 2;

        /**
         * A minimal window.
         */
        static const int LIGHTWEIGHT = 3;
    };

} // namespace cyder

#endif //HELLOSKIA_WINDOWTYPE_H
