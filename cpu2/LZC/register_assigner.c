/*
 Frida16_32 Project
 
 MIT License

 Copyright (c) 2025 FridaDEV

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "../RAM/mem.h"

byte_t TellMeWhatRegisterThisWas(const char ident)
{
    switch (ident) {
        case 'a':
            return 0b00000000;
        case 'b':
            return 0b00000001;
        case 'c':
            return 0b00000010;
        case 'd':
            return 0b00000011;
        case 'e':
            return 0b00000100;
        case 'f':
            return 0b00000101;
        case 'g':
            return 0b00000110;
        case 'h':
            return 0b00000111;
        case 'p':
            return 0b00001000;
        default:
            return 0;
    }
}
