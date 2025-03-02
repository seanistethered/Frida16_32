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

#include "function_compiler.h"
#include "../RAM/mem.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// compiler variables
extern uint16_t current_ram_address;
extern function_t function_cache[256];
extern function_t loop_cache[256];
extern uint16_t current_function;
extern uint16_t current_loop;
extern uint16_t instruction_ram[256];
extern uint16_t current_instruction;

void compiler_reset(void)
{
    // reset compiler
    current_ram_address = 10;
    current_instruction = 0;
    current_function = 0;
    current_loop = 0;
    memset(function_cache, 0, sizeof(function_cache));
    memset(loop_cache, 0, sizeof(loop_cache));
    memset(instruction_ram, 0, sizeof(instruction_ram));
}

void soc_reset(void)
{
    // reset ram
    byte_t *ram = intl_ram_handoff();
    memset(ram, 0, sizeof(byte_t) * 2048);
}
