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

#include "mem.h"

static byte_t ram[2048]; // 2048 bit ram

// 8 bit functions
byte_t ram_read(uint16_t addr)
{
    return ram[addr];
}

void ram_write(uint16_t addr, byte_t value)
{
    ram[addr] = value;
}

// 16bit functions
uint16_t ram_read16(uint16_t addr)
{
    uint16_t *address_ptr = (uint16_t*)&ram[addr];
    return *address_ptr;
}

void ram_write16(uint16_t addr, uint16_t value)
{
    ram[addr] = value;
}

// pointer functions
byte_t ram_ptr_read(uint16_t addr)
{
    return ram[ram[addr]];
}

uint16_t ram_ptr_read16(uint16_t addr)
{
    uint16_t *address_ptr = (uint16_t*)&ram[ram[addr]];
    return *address_ptr;
}

// INTERNAL FUNCTIONS //
byte_t* intl_ram_handoff(void)
{
    return &ram[0];
}
