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
#include <stdio.h>
#include <string.h>

byte_t getValueByChar(const char *value)
{
    byte_t decoded_value = atoi(value);
    if(decoded_value == 0)
    {
        if(strcmp(value, "0") == 0)
        {
            // actual 0, return 0
            return 0;
        } else {
            // return utf8 value
            return value[0];
        }
    }
    return decoded_value;
}

byte_t isBuffer(const char *value)
{
    byte_t decoded_value = atoi(value);
    if(decoded_value == 0)
    {
        if(strcmp(value, "0") == 0)
        {
            // actual 0, return 0
            return 0;
        } else {
            // return utf8 value
            size_t size = strlen(value);
            if(size > 1)
            {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}
