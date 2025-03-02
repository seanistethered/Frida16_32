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

#include "jump_builder.h"

#include <stdio.h>

jump_register_t jump_registry[256];
byte_t jump_registry_count = 0;
extern uint16_t instruction_ram[256];

// if someone writes in their code that they wanna jump to a not yet compiled instruction things might get fucked up
// so i wrote these helper functions in the compiler
void add_jump_registry(uint16_t offset, uint16_t iram_slice)
{
    jump_register_t register_slice;
    register_slice.offset_addr = offset;
    register_slice.iram_slice = iram_slice;
    jump_registry[jump_registry_count] = register_slice;
    jump_registry_count++;
}

void finalise_jumps(void)
{
    for(int i = 0; i < jump_registry_count; i++)
    {
        jump_register_t register_slice = jump_registry[i];
        uint16_t placeholder_offset_addr = register_slice.offset_addr;
        uint16_t jmp_offset = instruction_ram[register_slice.iram_slice];
        printf("[jb] placeholder_at_addr: 0x%04X, replacement: 0x%04X\n", placeholder_offset_addr, jmp_offset);
        ram_write16(register_slice.offset_addr, instruction_ram[register_slice.iram_slice]);
    }
}
