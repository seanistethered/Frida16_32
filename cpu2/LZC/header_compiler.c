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

#include "lazy_compiler.h"
#include "../RAM/mem.h"

#include <stdio.h>

extern uint16_t current_ram_address;

uint16_t getFunctionOffset(const char *name);

void compile_header(void)
{
    // getting offset of main function
    uint16_t offset = getFunctionOffset("main");
    printf("[hc] found \"main\" at -> 0x%04X\n", offset);
    
    // writting call instruction into header
    ram_write(1, cpu_cal);
    ram_write16(2, offset);
    
    // writting exit instructions, so when main function returns it gonna exit
    ram_write(4, cpu_exit);
    printf("[hc] building header done\n");
}
