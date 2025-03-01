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

// main instructions
#define cpu_exit 0b00000000 // (exits execution)
#define cpu_load 0b00000001 // (loads value to register)
#define cpu_st   0b00000010 // (string print to stdout)

// memory handling instructions
#define cpu_mwrt 0b00000011 // (memory write)
#define cpu_rwrt 0b00000100 // (register write)

// math instructions
#define cpu_add 0b000000101 // (additions register values)
#define cpu_sub 0b000000110 // (substract register values)
#define cpu_mul 0b000000111 // (muliplies register values)
#define cpu_div 0b000001000 // (divides register values)

// some other instructions
#define cpu_cpy 0b000001001 // (copies register values)
#define cpu_mov 0b000001010 // (swaps register values)
#define cpu_jmp 0b000001011 // (jumps to certain address)
#define cpu_cal 0b000001100
#define cpu_ret 0b000001101

// comparison
#define cpu_je  0b000001110 // (jump if registers equal)
#define cpu_jg  0b000001111 // (jump if registers greater)
#define cpu_jl  0b000010000 // (jump if registers less)

#define cpu_spw 0b000010001 // stackpointer write
#define cpu_spr 0b000010010 // stackpointer read
