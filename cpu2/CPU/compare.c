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

#include "compare.h"
#include "reg_utils.h"

void core_je(core_t *core)
{
    byte_t reg_addr_1 = pc_count_up_and_read(core);
    byte_t reg_addr_2 = pc_count_up_and_read(core);
    pc_count_up_and_read(core);
    uint16_t mem_addr = ram_read16(core->pc);
    pc_count_up_and_read(core);
    if(cpuRegisterReadNC(core, reg_addr_1) == cpuRegisterReadNC(core, reg_addr_2))
    {
        core->pc = mem_addr - 1;
    }
}

void core_jg(core_t *core)
{
    byte_t reg_addr_1 = pc_count_up_and_read(core);
    byte_t reg_addr_2 = pc_count_up_and_read(core);
    pc_count_up_and_read(core);
    uint16_t mem_addr = ram_read16(core->pc);
    pc_count_up_and_read(core);
    if(cpuRegisterReadNC(core, reg_addr_1) > cpuRegisterReadNC(core, reg_addr_2))
    {
        core->pc = mem_addr - 1;
    }
}

void core_jl(core_t *core)
{
    byte_t reg_addr_1 = pc_count_up_and_read(core);
    byte_t reg_addr_2 = pc_count_up_and_read(core);
    pc_count_up_and_read(core);
    uint16_t mem_addr = ram_read16(core->pc);
    pc_count_up_and_read(core);
    if(cpuRegisterReadNC(core, reg_addr_1) < cpuRegisterReadNC(core, reg_addr_2))
    {
        core->pc = mem_addr - 1;
    }
}
