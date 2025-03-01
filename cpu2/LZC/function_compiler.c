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
#include "register_assigner.h"
#include "value_assigner.h"
#include "buffer_assigner.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
    uint16_t start;
    uint16_t end;
} function_t;

extern uint16_t current_ram_address;
function_t function_cache[256];
function_t loop_cache[256];
uint16_t current_function = 0;
uint16_t current_loop = 0;

function_t* getNewUnlabledFunction(void)
{
    current_function++;
    return &function_cache[current_function - 1];
}

void assignFunctionName(const char *name, function_t *function)
{
    size_t namesize = strlen(name);
    function->name = malloc(sizeof(namesize));
    strcpy(function->name, name);
}

void stapleFunction(function_t *function)
{
    if(function->start  == 0)
    {
        function->start = current_ram_address + 1;
        return;
    } else if(function->end == 0)
    {
        function->end = current_ram_address;
    }
}

uint16_t getFunctionOffset(const char *name)
{
    for(int i = 0; i < current_function; i++)
    {
        if(strcmp(function_cache[i].name, name) == 0)
        {
            return function_cache[i].start;
        }
    }
    return 0;
}

void compile_function(const char *name, const char* args[][10])
{
    // preset function
    function_t *function = getNewUnlabledFunction();
    assignFunctionName(name, function);
    
    // assign start offset
    stapleFunction(function);
    printf("[fc] function \"%s\" starts at 0x%04X\n", function->name, function->start);
    
    // building function
    for(int i = 0; args[i][0] != NULL; i++)
    {
        // building, idk
        if(strcmp(args[i][0], "exit") == 0)
        {
            lzc_build_exit_instruction();
        } else if(strcmp(args[i][0], "load") == 0)
        {
            lzc_build_load_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), getValueByChar(args[i][2]));
        } else if(strcmp(args[i][0], "output") == 0)
        {
            lzc_build_st_instruction(TellMeWhatRegisterThisWas(args[i][1][0]));
        } else if(strcmp(args[i][0], "mwrite") == 0)
        {
            lzc_build_mwrt_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), getValueByChar(args[i][2]));
        } else if(strcmp(args[i][0], "rwrite") == 0)
        {
            lzc_build_rwrt_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), getValueByChar(args[i][2]));
        } else if(strcmp(args[i][0], "addition") == 0)
        {
            lzc_build_add_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), TellMeWhatRegisterThisWas(args[i][2][0]));
        } else if(strcmp(args[i][0], "subtract") == 0)
        {
            lzc_build_sub_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), TellMeWhatRegisterThisWas(args[i][2][0]));
        } else if(strcmp(args[i][0], "multiply") == 0)
        {
            lzc_build_mul_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), TellMeWhatRegisterThisWas(args[i][2][0]));
        } else if(strcmp(args[i][0], "divide") == 0)
        {
            lzc_build_div_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), TellMeWhatRegisterThisWas(args[i][2][0]));
        } else if(strcmp(args[i][0], "copy") == 0)
        {
            lzc_build_cpy_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), TellMeWhatRegisterThisWas(args[i][2][0]));
        } else if(strcmp(args[i][0], "move") == 0)
        {
            lzc_build_mov_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), TellMeWhatRegisterThisWas(args[i][2][0]));
        } else if(strcmp(args[i][0], "isequal") == 0)
        {
            lzc_build_je_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), TellMeWhatRegisterThisWas(args[i][2][0]), getValueByChar(args[i][3]));
        } else if(strcmp(args[i][0], "isgreater") == 0)
        {
            lzc_build_jg_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), TellMeWhatRegisterThisWas(args[i][2][0]), getValueByChar(args[i][3]));
        } else if(strcmp(args[i][0], "isless") == 0)
        {
            lzc_build_jl_instruction(TellMeWhatRegisterThisWas(args[i][1][0]), TellMeWhatRegisterThisWas(args[i][2][0]), getValueByChar(args[i][3]));
        } else if(strcmp(args[i][0], "return") == 0)
        {
            lzc_build_return_instruction();
        } else if(strcmp(args[i][0], "loop") == 0)
        {
            stapleFunction(&loop_cache[current_loop]);
            printf("[fc] loop starts at 0x%04X\n", loop_cache[current_loop].start);
            current_loop++;
        } else if(strcmp(args[i][0], "end") == 0)
        {
            current_loop--;
            stapleFunction(&loop_cache[current_loop]);
            printf("[fc] loop starts at 0x%04X\n", loop_cache[current_loop].end);
            lzc_build_jmp_direct_instruction(loop_cache[current_loop].start);
        }
        
        // function stuff
        if(strcmp(args[i][0], "call") == 0)
        {
            printf("[fc] function call to \"%s\" added\n", args[i][1]);
            size_t namesize = strlen(args[i][1]);
            char *name = malloc(namesize);
            strcpy(name, args[i][1]);
            byte_t arggs = 0;
            for(int j = 2; args[i][j] != NULL; j++)
            {
                arggs++;
            }
            for(int j = 1 + arggs; j != 1; j--)
            {
                if(isBuffer(args[i][j]))
                {
                    assign_buffer_reverse(args[i][j]);
                } else {
                    lzc_build_spw_instruction(getValueByChar(args[i][j]));
                }
            }
            lzc_build_call_instruction(getFunctionOffset(name));
            free(name);
        }
    }
    
    // implement return into function
    lzc_build_return_instruction();
    
    // assign end offset
    stapleFunction(function);
    printf("[fc] function \"%s\" ends at 0x%04X\n", function->name, function->end);
}
