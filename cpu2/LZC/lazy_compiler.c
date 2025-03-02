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
#include "jump_builder.h"
#include <stdio.h>

uint16_t current_ram_address = 10;
uint16_t instruction_ram[256];
uint16_t current_instruction = 0;

// lazy compiler helper
uint16_t lzc_helper_count_up(void)
{
    current_ram_address++;
    return current_ram_address;
}

uint16_t instruct_offset_giver(const char *name)
{
    current_instruction++;
    uint16_t offset = lzc_helper_count_up();
    printf("[lzc] %s instruction build at -> 0x%04X\n", name, offset);
    instruction_ram[current_instruction - 1] = offset;
    return instruction_ram[current_instruction - 1];
}

// low level lazy compiler
void lzc_build_exit_instruction(void)
{
    ram_write(instruct_offset_giver("exit"), cpu_exit);
}

void lzc_build_load_instruction(byte_t reg_addr, byte_t value)
{
    ram_write(instruct_offset_giver("load"), cpu_load);
    ram_write(lzc_helper_count_up(), reg_addr);
    ram_write(lzc_helper_count_up(), value);
}

void lzc_build_st_instruction(byte_t reg_addr)
{
    ram_write(instruct_offset_giver("output"), cpu_st);
    ram_write(lzc_helper_count_up(), reg_addr);
}

void lzc_build_mwrt_instruction(byte_t reg_addr, uint16_t mem_addr)
{
    ram_write(instruct_offset_giver("mwrite"), cpu_mwrt);
    ram_write(lzc_helper_count_up(), reg_addr);
    lzc_helper_count_up();
    ram_write16(current_ram_address, mem_addr);
    lzc_helper_count_up();
}

void lzc_build_rwrt_instruction(byte_t reg_addr, byte_t mem_addr)
{
    ram_write(instruct_offset_giver("rwrite"), cpu_rwrt);
    ram_write(lzc_helper_count_up(), reg_addr);
    lzc_helper_count_up();
    ram_write16(current_ram_address, mem_addr);
    lzc_helper_count_up();
}

void lzc_build_add_instruction(byte_t reg_addr_1, byte_t reg_addr_2)
{
    ram_write(instruct_offset_giver("add"), cpu_add);
    ram_write(lzc_helper_count_up(), reg_addr_1);
    ram_write(lzc_helper_count_up(), reg_addr_2);
}

void lzc_build_sub_instruction(byte_t reg_addr_1, byte_t reg_addr_2)
{
    ram_write(instruct_offset_giver("sub"), cpu_sub);
    ram_write(lzc_helper_count_up(), reg_addr_1);
    ram_write(lzc_helper_count_up(), reg_addr_2);
}

void lzc_build_mul_instruction(byte_t reg_addr_1, byte_t reg_addr_2)
{
    ram_write(instruct_offset_giver("mul"), cpu_mul);
    ram_write(lzc_helper_count_up(), reg_addr_1);
    ram_write(lzc_helper_count_up(), reg_addr_2);
}

void lzc_build_div_instruction(byte_t reg_addr_1, byte_t reg_addr_2)
{
    ram_write(instruct_offset_giver("div"), cpu_div);
    ram_write(lzc_helper_count_up(), reg_addr_1);
    ram_write(lzc_helper_count_up(), reg_addr_2);
}

void lzc_build_cpy_instruction(byte_t reg_addr_1, byte_t reg_addr_2)
{
    ram_write(instruct_offset_giver("cpy"), cpu_cpy);
    ram_write(lzc_helper_count_up(), reg_addr_1);
    ram_write(lzc_helper_count_up(), reg_addr_2);
}

void lzc_build_mov_instruction(byte_t reg_addr_1, byte_t reg_addr_2)
{
    ram_write(instruct_offset_giver("mov"), cpu_mov);
    ram_write(lzc_helper_count_up(), reg_addr_1);
    ram_write(lzc_helper_count_up(), reg_addr_2);
}

void lzc_build_jmp_instruction(byte_t addr)
{
    uint16_t offset = instruct_offset_giver("jmp");
    ram_write(offset, cpu_jmp);
    uint16_t offset_of_jump_address = lzc_helper_count_up();
    ram_write16(current_ram_address, 0xffff);
    lzc_helper_count_up();
    add_jump_registry(offset_of_jump_address, current_instruction + addr);
}

void lzc_build_jmp_direct_instruction(uint16_t addr)
{
    ram_write(instruct_offset_giver("jmp"), cpu_jmp);
    lzc_helper_count_up();
    ram_write16(current_ram_address, addr);
    lzc_helper_count_up();
    printf("[lzc] info: jumps to 0x%04X\n", addr);
}

void lzc_build_call_instruction(byte_t addr)
{
    ram_write(instruct_offset_giver("call"), cpu_cal);
    lzc_helper_count_up();
    ram_write16(current_ram_address, addr);
    lzc_helper_count_up();
}

void lzc_build_return_instruction(void)
{
    ram_write(instruct_offset_giver("return"), cpu_ret);
}

void lzc_build_je_instruction(byte_t reg_addr_1, byte_t reg_addr_2, uint16_t mem_addr)
{
    uint16_t offset = instruct_offset_giver("isequal");
    ram_write(offset, cpu_je);
    ram_write(lzc_helper_count_up(), reg_addr_1);
    ram_write(lzc_helper_count_up(), reg_addr_2);
    uint16_t offset_of_jump_address = lzc_helper_count_up();
    ram_write16(current_ram_address, 0xffff);
    lzc_helper_count_up();
    add_jump_registry(offset_of_jump_address, current_instruction + mem_addr);
    
}

void lzc_build_jg_instruction(byte_t reg_addr_1, byte_t reg_addr_2, uint16_t mem_addr)
{
    uint16_t offset = instruct_offset_giver("isgreater");
    ram_write(offset, cpu_jg);
    ram_write(lzc_helper_count_up(), reg_addr_1);
    ram_write(lzc_helper_count_up(), reg_addr_2);
    uint16_t offset_of_jump_address = lzc_helper_count_up();
    ram_write16(current_ram_address, 0xffff);
    lzc_helper_count_up();
    add_jump_registry(offset_of_jump_address, current_instruction + mem_addr);
}

void lzc_build_jl_instruction(byte_t reg_addr_1, byte_t reg_addr_2, uint16_t mem_addr)
{
    uint16_t offset = instruct_offset_giver("isless");
    ram_write(offset, cpu_jl);
    ram_write(lzc_helper_count_up(), reg_addr_1);
    ram_write(lzc_helper_count_up(), reg_addr_2);
    uint16_t offset_of_jump_address = lzc_helper_count_up();
    ram_write16(current_ram_address, 0xffff);
    lzc_helper_count_up();
    add_jump_registry(offset_of_jump_address, current_instruction + mem_addr);
}

void lzc_build_spw_instruction(byte_t value)
{
    ram_write(instruct_offset_giver("spwrite"), cpu_spw);
    ram_write(lzc_helper_count_up(), value);
}

void lzc_build_spr_instruction(void)
{
    ram_write(instruct_offset_giver("spread"), cpu_spr);
}
