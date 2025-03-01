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

#include "reg_utils.h"
#include "sp_utils.h"

byte_t cpuRegisterReadNC(core_t *core, byte_t addr)
{
    if(addr == 0b00001000)
    {
        return core->sp[core->sp_track - 1];
    }
    return core->reg[addr];
}

byte_t cpuRegisterRead(core_t *core, byte_t addr)
{
    if(addr == 0b00001000)
    {
        core->sp_track--;
        return core->sp[core->sp_track];
    }
    return core->reg[addr];
}

void cpuRegisterWrite(core_t *core, byte_t addr, byte_t value)
{
    if(addr == 0b00001000)
    {
        core->sp_track++;
        core->sp[core->sp_track] = value;
        return;
    }
    core->reg[addr] = value;
}
