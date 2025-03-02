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
        case 'A':
            return 0b00000000;
        case 'B':
            return 0b00000001;
        case 'C':
            return 0b00000010;
        case 'D':
            return 0b00000011;
        case 'E':
            return 0b00000100;
        case 'F':
            return 0b00000101;
        case 'G':
            return 0b00000110;
        case 'H':
            return 0b00000111;
        case 'P':
            return 0b00001000;
        default:
            return 0;
    }
}

char TellMeWhatLetterRegisterThisWas(byte_t addr)
{
    switch (addr) {
        case 0b00000000:
            return 'A';
        case 0b00000001:
            return 'B';
        case 0b00000010:
            return 'C';
        case 0b00000011:
            return 'D';
        case 0b00000100:
            return 'E';
        case 0b00000101:
            return 'F';
        case 0b00000110:
            return 'G';
        case 0b00000111:
            return 'H';
        case 0b00001000:
            return 'P';
        default:
            return 0;
    }
}
