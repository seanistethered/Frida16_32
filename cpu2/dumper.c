//
//  dumper.c
//  cpu2
//
//  Created by fridakitten on 02.03.25.
//

#include "RAM/mem.h"
#include "LZC/register_assigner.h"
#include "cpu_instruction_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* integer_easifyier(uint16_t integer)
{
    char *buffer = malloc(sizeof(char) * 256);
    sprintf(buffer, "0x%04X(%d)", integer, integer);
    return buffer;
}

char *register_formatter(uint16_t integer, char reg)
{
    char *buffer = malloc(sizeof(char) * 256);
    sprintf(buffer, "0x%04X(%c)", integer, reg);
    return buffer;
}

void frida816_revser_engineerer(uint16_t start)
{
    uint16_t pc_addr = start;
    uint16_t ex;
    
    uint16_t offset_cache[10];
    char cache[10];
    
    while(1)
    {
        pc_addr++;
        ex = ram_read(pc_addr);
        switch(ex)
        {
            case cpu_exit:
                printf("0x%04X:\texit\n", pc_addr);
                return;
            case cpu_load:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                printf("0x%04X:\tload\t%s\t->\t%s\n", pc_addr, integer_easifyier(ram_read(pc_addr + 2)), register_formatter(offset_cache[0], cache[0]));
                pc_addr = pc_addr + 2;
                break;
            case cpu_st:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                printf("0x%04X:\tst\t\t%s\t->\tstdio\n", pc_addr, register_formatter(offset_cache[0], cache[0]));
                pc_addr = pc_addr + 1;
                break;
            case cpu_mwrt:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                printf("0x%04X:\tmwrt\t%s\t->\tmemory(%s)\n", pc_addr, register_formatter(offset_cache[0], cache[0]), integer_easifyier(ram_read16(pc_addr + 2)));
                pc_addr = pc_addr + 3;
                break;
            case cpu_rwrt:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                printf("0x%04X:\trwrt\tmemory(%s)\t->\t%s\n", pc_addr, integer_easifyier(ram_read16(pc_addr + 2)), register_formatter(offset_cache[0], cache[0]));
                pc_addr = pc_addr + 3;
                break;
            case cpu_add:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                offset_cache[1] = ram_read(pc_addr + 2);
                cache[1] = TellMeWhatLetterRegisterThisWas(offset_cache[1]);
                printf("0x%04X:\tadd\t\t%s\t->\t%s\n", pc_addr, register_formatter(offset_cache[1], cache[1]), register_formatter(offset_cache[0], cache[0]));
                pc_addr = pc_addr + 2;
                break;
            case cpu_sub:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                offset_cache[1] = ram_read(pc_addr + 2);
                cache[1] = TellMeWhatLetterRegisterThisWas(offset_cache[1]);
                printf("0x%04X:\tsub\t\t%s\t->\t%s\n", pc_addr, register_formatter(offset_cache[1], cache[1]), register_formatter(offset_cache[0], cache[0]));
                pc_addr = pc_addr + 2;
                break;
            case cpu_mul:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                offset_cache[1] = ram_read(pc_addr + 2);
                cache[1] = TellMeWhatLetterRegisterThisWas(offset_cache[1]);
                printf("0x%04X:\tmul\t\t%s\t->\t%s\n", pc_addr, register_formatter(offset_cache[1], cache[1]), register_formatter(offset_cache[0], cache[0]));
                pc_addr = pc_addr + 2;
                break;
            case cpu_div:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                offset_cache[1] = ram_read(pc_addr + 2);
                cache[1] = TellMeWhatLetterRegisterThisWas(offset_cache[1]);
                printf("0x%04X:\tdiv\t\t%s\t->\t%s\n", pc_addr, register_formatter(offset_cache[1], cache[1]), register_formatter(offset_cache[0], cache[0]));
                pc_addr = pc_addr + 2;
                break;
            case cpu_cpy:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                offset_cache[1] = ram_read(pc_addr + 2);
                cache[1] = TellMeWhatLetterRegisterThisWas(offset_cache[1]);
                printf("0x%04X:\tcpy\t\t%s\t->\t%s\n", pc_addr, register_formatter(offset_cache[1], cache[1]), register_formatter(offset_cache[0], cache[0]));
                pc_addr = pc_addr + 2;
                break;
            case cpu_mov:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                offset_cache[1] = ram_read(pc_addr + 2);
                cache[1] = TellMeWhatLetterRegisterThisWas(offset_cache[1]);
                printf("0x%04X:\tmov\t\t%s\t<>\t%s\n", pc_addr, register_formatter(offset_cache[1], cache[1]), register_formatter(offset_cache[0], cache[0]));
                pc_addr = pc_addr + 2;
                break;
            case cpu_jmp:
                printf("0x%04X:\tjmp\t\t%s\n", pc_addr, integer_easifyier(ram_read16(pc_addr + 1)));
                pc_addr = pc_addr + 2;
                break;
            case cpu_cal:
                printf("0x%04X:\tcal\t\t%s\n", pc_addr, integer_easifyier(ram_read16(pc_addr + 1)));
                pc_addr = pc_addr + 2;
                break;
            case cpu_ret:
                printf("0x%04X:\tret\n", pc_addr);
                break;
            case cpu_je:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                offset_cache[1] = ram_read(pc_addr + 2);
                cache[1] = TellMeWhatLetterRegisterThisWas(offset_cache[1]);
                printf("0x%04X:\tje\t\t(%s\t==\t%s)\tPC\t->\t%s\n", pc_addr, register_formatter(offset_cache[0], cache[0]), register_formatter(offset_cache[1], cache[1]), integer_easifyier(ram_read16(pc_addr + 3)));
                pc_addr = pc_addr + 4;
                break;
            case cpu_jl:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                offset_cache[1] = ram_read(pc_addr + 2);
                cache[1] = TellMeWhatLetterRegisterThisWas(offset_cache[1]);
                printf("0x%04X:\tjl\t\t(%s\t<\t%s)\tPC\t->\t%s\n", pc_addr, register_formatter(offset_cache[0], cache[0]), register_formatter(offset_cache[1], cache[1]), integer_easifyier(ram_read16(pc_addr + 3)));
                pc_addr = pc_addr + 4;
                break;
            case cpu_jg:
                offset_cache[0] = ram_read(pc_addr + 1);
                cache[0] = TellMeWhatLetterRegisterThisWas(offset_cache[0]);
                offset_cache[1] = ram_read(pc_addr + 2);
                cache[1] = TellMeWhatLetterRegisterThisWas(offset_cache[1]);
                printf("0x%04X:\tjg\t\t(%s\t>\t%s)\tPC\t->\t%s\n", pc_addr, register_formatter(offset_cache[0], cache[0]), register_formatter(offset_cache[1], cache[1]), integer_easifyier(ram_read16(pc_addr + 3)));
                pc_addr = pc_addr + 4;
                break;
            case cpu_spw:
                printf("0x%04X:\tspw\t\t%s\n", pc_addr, integer_easifyier(ram_read16(pc_addr + 1)));
                pc_addr = pc_addr + 1;
                break;
            case cpu_spr:
                printf("0x%04X:\tspr\t\t%s\n", pc_addr, integer_easifyier(ram_read16(pc_addr + 1)));
                pc_addr = pc_addr + 1;
                break;
            default:
                printf("unknown instruction\n");
        }
    }
}
