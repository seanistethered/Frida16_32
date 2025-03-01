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

#include "../cpu_instruction_list.h"
#include "../RAM/mem.h"

void lzc_build_exit_instruction(void);
void lzc_build_load_instruction(byte_t reg_addr, byte_t value);
void lzc_build_st_instruction(byte_t reg_addr);

void lzc_build_mwrt_instruction(byte_t reg_addr, uint16_t mem_addr);
void lzc_build_rwrt_instruction(byte_t reg_addr, uint16_t mem_addr);

void lzc_build_add_instruction(byte_t reg_addr_1, byte_t reg_addr_2);
void lzc_build_sub_instruction(byte_t reg_addr_1, byte_t reg_addr_2);
void lzc_build_mul_instruction(byte_t reg_addr_1, byte_t reg_addr_2);
void lzc_build_div_instruction(byte_t reg_addr_1, byte_t reg_addr_2);

void lzc_build_cpy_instruction(byte_t reg_addr_1, byte_t reg_addr_2);
void lzc_build_mov_instruction(byte_t reg_addr_1, byte_t reg_addr_2);

void lzc_build_jmp_instruction(byte_t addr);
void lzc_build_call_instruction(byte_t addr);
void lzc_build_return_instruction(void);

void lzc_build_je_instruction(byte_t reg_addr_1, byte_t reg_addr_2, uint16_t mem_addr);
void lzc_build_jg_instruction(byte_t reg_addr_1, byte_t reg_addr_2, uint16_t mem_addr);
void lzc_build_jl_instruction(byte_t reg_addr_1, byte_t reg_addr_2, uint16_t mem_addr);

// !INTERNAL INSTRUCTION! //
void lzc_build_spw_instruction(byte_t value);
void lzc_build_spr_instruction(void);
void lzc_build_jmp_direct_instruction(uint16_t addr);
