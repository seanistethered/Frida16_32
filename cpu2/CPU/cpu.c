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

#include "cpu.h"
#include "../cpu_instruction_list.h"

#include "helper.h"
#include "math.h"
#include "compare.h"
#include "sp_utils.h"
#include "reg_utils.h"

// core instructions
void core_load(core_t *core)
{
    byte_t addr = pc_count_up_and_read(core);
    cpuRegisterWrite(core, addr, pc_count_up_and_read(core));
}

void core_sta(core_t *core)
{
    fprintf(stdout, "%c", cpuRegisterRead(core, pc_count_up_and_read(core)));
}

void core_sti(core_t *core)
{
    core->reg[0] = getchar();
}

void core_mwrt(core_t *core)
{
    byte_t reg_addr = pc_count_up_and_read(core);
    uint16_t mem_addr = pc_count_up_and_read_16(core);
    ram_write16(mem_addr, cpuRegisterRead(core, reg_addr));
}

void core_rwrt(core_t *core)
{
    byte_t reg_addr = pc_count_up_and_read(core);
    uint16_t mem_addr = pc_count_up_and_read_16(core);
    cpuRegisterWrite(core, reg_addr, ram_read(mem_addr));
}

void core_cpy(core_t *core)
{
    byte_t reg_addr_1 = pc_count_up_and_read(core);
    byte_t reg_addr_2 = pc_count_up_and_read(core);
    cpuRegisterWrite(core, reg_addr_1, cpuRegisterRead(core, reg_addr_2));
}

void core_mov(core_t *core)
{
    byte_t reg_addr_1 = pc_count_up_and_read(core);
    byte_t reg_addr_2 = pc_count_up_and_read(core);
    cpuRegisterWrite(core, 0b00001000, cpuRegisterRead(core, reg_addr_1));
    cpuRegisterWrite(core, reg_addr_1, cpuRegisterRead(core, reg_addr_2));
    cpuRegisterWrite(core, reg_addr_2, cpuRegisterRead(core, 0b00001000));
}

void core_jmp(core_t *core)
{
    uint16_t pc_addr = pc_count_up_and_read_16(core) - 1;
    core->pc = pc_addr;
}

void core_cal(core_t *core)
{
    // storing return address
    core->rt_cout++;
    core->rt_tree[core->rt_cout] = core->pc;
    // calling function
    uint16_t pc_addr = pc_count_up_and_read_16(core) - 1;
    core->pc = pc_addr;
}

void core_ret(core_t *core)
{
    // going back
    core->pc = core->rt_tree[core->rt_cout] + 2;
    core->rt_tree[core->rt_cout] = 0;
    core->rt_cout--;
}

void core_exit(core_t *core)
{
    core->status = 0;
}

void core_setup(core_t *core, uint16_t pc)
{
    // check if core is busy rn
    if(core->status == 0)
    {
        // prepare core
        core->pc = pc;
        core->rt_cout = 0;
        core->sp_track = 0;
        memset(core->rt_tree, 0, sizeof(core->rt_tree));
        memset(core->sp, 0, sizeof(core->sp));
        memset(core->reg, 0, sizeof(core->reg));
        // setting cores executable register
        core->ex = ram_read(core->pc);
    }
}

// core it self
void core_run(core_t *core)
{
    // setting up core
    core->sp_track = 0;
    core->status = 1;
    
    // core loop
    while(1)
    {
        switch(core->ex) {
            case cpu_exit:
                core_exit(core);
                return;
            case cpu_load:
                core_load(core);
                break;
            case cpu_st:
                core_sta(core);
                break;
            case cpu_mwrt:
                core_mwrt(core);
                break;
            case cpu_rwrt:
                core_rwrt(core);
                break;
            case cpu_add:
                core_add(core);
                break;
            case cpu_sub:
                core_sub(core);
                break;
            case cpu_mul:
                core_mul(core);
                break;
            case cpu_div:
                core_div(core);
                break;
            case cpu_cpy:
                core_cpy(core);
                break;
            case cpu_mov:
                core_mov(core);
                break;
            case cpu_jmp:
                core_jmp(core);
                break;
            case cpu_cal:
                core_cal(core);
                break;
            case cpu_ret:
                core_ret(core);
                break;
            case cpu_je:
                core_je(core);
                break;
            case cpu_jg:
                core_jg(core);
                break;
            case cpu_jl:
                core_jl(core);
                break;
            case cpu_spw:
                core_spw(core);
                break;
            case cpu_spr:
                core_rpw(core);
                break;
            default:
                return;
        }
        pc_count_up(core);
    }
}
