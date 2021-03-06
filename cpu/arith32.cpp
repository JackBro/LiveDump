/////////////////////////////////////////////////////////////////////////
// $Id: arith32.cc,v 1.7 2001/11/17 22:22:03 bdenney Exp $
/////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2001  MandrakeSoft S.A.
//
//    MandrakeSoft S.A.
//    43, rue d'Aboukir
//    75002 Paris - France
//    http://www.linux-mandrake.com/
//    http://www.mandrakesoft.com/
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA





#define NEED_CPU_REG_SHORTCUTS 1
#include "bochs.h"
#define LOG_THIS bx_cpu.


  void
bx_cpu_c::INC_ERX(BxInstruction_t *i)
{
  Bit32u erx;

  erx = ++ bx_cpu. gen_reg[i->b1 & 0x07].erx;
  SET_FLAGS_OSZAP_32(0, 0, erx, BX_INSTR_INC32);
}

  void
bx_cpu_c::DEC_ERX(BxInstruction_t *i)
{
  Bit32u erx;

  erx = -- bx_cpu. gen_reg[i->b1 & 0x07].erx;
  SET_FLAGS_OSZAP_32(0, 0, erx, BX_INSTR_DEC32);
}




  void
bx_cpu_c::ADD_EdGd(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, sum_32;

    /* op2_32 is a register, i->rm_addr is an index of a register */
    op2_32 = BX_READ_32BIT_REG(i->nnn);

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    sum_32 = op1_32 + op2_32;

    /* now write sum back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, sum_32);
      }
    else {
      write_RMW_virtual_dword(sum_32);
      }

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, sum_32, BX_INSTR_ADD32);
}


  void
bx_cpu_c::ADD_GdEd(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, sum_32;

    /* op1_32 is a register, i->rm_addr is an index of a register */
    op1_32 = BX_READ_32BIT_REG(i->nnn);

    /* op2_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op2_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op2_32);
      }

    sum_32 = op1_32 + op2_32;

    /* now write sum back to destination */
    BX_WRITE_32BIT_REG(i->nnn, sum_32);

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, sum_32, BX_INSTR_ADD32);
}


  void
bx_cpu_c::ADD_EAXId(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, sum_32;

    op1_32 = EAX;

    op2_32 = i->Id;

    sum_32 = op1_32 + op2_32;

    /* now write sum back to destination */
    EAX = sum_32;

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, sum_32, BX_INSTR_ADD32);
}

  void
bx_cpu_c::ADC_EdGd(BxInstruction_t *i)
{
  Boolean temp_CF;

  temp_CF = get_CF();


    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, sum_32;

    /* op2_32 is a register, i->rm_addr is an index of a register */
    op2_32 = BX_READ_32BIT_REG(i->nnn);

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    sum_32 = op1_32 + op2_32 + temp_CF;

    /* now write sum back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, sum_32);
      }
    else {
      write_RMW_virtual_dword(sum_32);
      }

    SET_FLAGS_OSZAPC_32_CF(op1_32, op2_32, sum_32, BX_INSTR_ADC32,
                              temp_CF);
}


  void
bx_cpu_c::ADC_GdEd(BxInstruction_t *i)
{
  Boolean temp_CF;

  temp_CF = get_CF();


    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, sum_32;

    /* op1_32 is a register, i->rm_addr is an index of a register */
    op1_32 = BX_READ_32BIT_REG(i->nnn);

    /* op2_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op2_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op2_32);
      }

    sum_32 = op1_32 + op2_32 + temp_CF;

    /* now write sum back to destination */
    BX_WRITE_32BIT_REG(i->nnn, sum_32);

    SET_FLAGS_OSZAPC_32_CF(op1_32, op2_32, sum_32, BX_INSTR_ADC32,
                             temp_CF);
}


  void
bx_cpu_c::ADC_EAXId(BxInstruction_t *i)
{
  Boolean temp_CF;

  temp_CF = get_CF();

    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, sum_32;

    op1_32 = EAX;

    op2_32 = i->Id;

    sum_32 = op1_32 + op2_32 + temp_CF;

    /* now write sum back to destination */
    EAX = sum_32;

    SET_FLAGS_OSZAPC_32_CF(op1_32, op2_32, sum_32, BX_INSTR_ADC32,
                           temp_CF);
}




  void
bx_cpu_c::SBB_EdGd(BxInstruction_t *i)
{
  Boolean temp_CF;

  temp_CF = get_CF();


    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, diff_32;

    /* op2_32 is a register, i->rm_addr is an index of a register */
    op2_32 = BX_READ_32BIT_REG(i->nnn);

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    diff_32 = op1_32 - (op2_32 + temp_CF);

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, diff_32);
      }
    else {
      write_RMW_virtual_dword(diff_32);
      }

    SET_FLAGS_OSZAPC_32_CF(op1_32, op2_32, diff_32, BX_INSTR_SBB32,
                              temp_CF);
}


  void
bx_cpu_c::SBB_GdEd(BxInstruction_t *i)
{
  Boolean temp_CF;

  temp_CF = get_CF();


    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, diff_32;

    /* op1_32 is a register, i->rm_addr is an index of a register */
    op1_32 = BX_READ_32BIT_REG(i->nnn);

    /* op2_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op2_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op2_32);
      }

    diff_32 = op1_32 - (op2_32 + temp_CF);

    /* now write diff back to destination */
    BX_WRITE_32BIT_REG(i->nnn, diff_32);

    SET_FLAGS_OSZAPC_32_CF(op1_32, op2_32, diff_32, BX_INSTR_SBB32,
                              temp_CF);
}


  void
bx_cpu_c::SBB_EAXId(BxInstruction_t *i)
{
  Boolean temp_CF;

  temp_CF = get_CF();

    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, diff_32;

    op1_32 = EAX;

    op2_32 = i->Id;

    diff_32 = op1_32 - (op2_32 + temp_CF);

    /* now write diff back to destination */
    EAX = diff_32;

    SET_FLAGS_OSZAPC_32_CF(op1_32, op2_32, diff_32, BX_INSTR_SBB32,
                              temp_CF);
}



  void
bx_cpu_c::SBB_EdId(BxInstruction_t *i)
{
  Boolean temp_CF;

  temp_CF = get_CF();


    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, diff_32;

    op2_32 = i->Id;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    diff_32 = op1_32 - (op2_32 + temp_CF);

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, diff_32);
      }
    else {
      write_RMW_virtual_dword(diff_32);
      }

    SET_FLAGS_OSZAPC_32_CF(op1_32, op2_32, diff_32, BX_INSTR_SBB32,
                              temp_CF);
}


  void
bx_cpu_c::SUB_EdGd(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, diff_32;

    /* op2_32 is a register, i->rm_addr is an index of a register */
    op2_32 = BX_READ_32BIT_REG(i->nnn);

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    diff_32 = op1_32 - op2_32;

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, diff_32);
      }
    else {
      write_RMW_virtual_dword(diff_32);
      }

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, diff_32, BX_INSTR_SUB32);
}


  void
bx_cpu_c::SUB_GdEd(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, diff_32;

    /* op1_32 is a register, i->rm_addr is an index of a register */
    op1_32 = BX_READ_32BIT_REG(i->nnn);

    /* op2_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op2_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op2_32);
      }

    diff_32 = op1_32 - op2_32;

    /* now write diff back to destination */
    BX_WRITE_32BIT_REG(i->nnn, diff_32);

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, diff_32, BX_INSTR_SUB32);
}

  void
bx_cpu_c::SUB_EAXId(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, diff_32;

    op1_32 = EAX;

    op2_32 = i->Id;

    diff_32 = op1_32 - op2_32;

    /* now write diff back to destination */
    EAX = diff_32;

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, diff_32, BX_INSTR_SUB32);
}


  void
bx_cpu_c::CMP_EdGd(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, diff_32;

    /* op2_32 is a register, i->rm_addr is an index of a register */
    op2_32 = BX_READ_32BIT_REG(i->nnn);

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    diff_32 = op1_32 - op2_32;

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, diff_32, BX_INSTR_CMP32);
}


  void
bx_cpu_c::CMP_GdEd(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, diff_32;

    /* op1_32 is a register, i->rm_addr is an index of a register */
    op1_32 = BX_READ_32BIT_REG(i->nnn);

    /* op2_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op2_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op2_32);
      }

    diff_32 = op1_32 - op2_32;

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, diff_32, BX_INSTR_CMP32);
}


  void
bx_cpu_c::CMP_EAXId(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, diff_32;

    op1_32 = EAX;

    op2_32 = i->Id;

    diff_32 = op1_32 - op2_32;

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, diff_32, BX_INSTR_CMP32);
}


  void
bx_cpu_c::CWDE(BxInstruction_t *i)
{
  /* CBW: no flags are effected */

    EAX = (Bit16s) AX;
}

  void
bx_cpu_c::CDQ(BxInstruction_t *i)
{
  /* CWD: no flags are affected */

    if (EAX & 0x80000000) {
      EDX = 0xFFFFFFFF;
      }
    else {
      EDX = 0x00000000;
      }
}

// Some info on the opcodes at {0F,A6} and {0F,A7}
// On 386 steps A0-B0:
//   {OF,A6} = XBTS
//   {OF,A7} = IBTS
// On 486 steps A0-B0:
//   {OF,A6} = CMPXCHG 8
//   {OF,A7} = CMPXCHG 16|32
//
// On 486 >= B steps, and further processors, the
// CMPXCHG instructions were moved to opcodes:
//   {OF,B0} = CMPXCHG 8
//   {OF,B1} = CMPXCHG 16|32

  void
bx_cpu_c::CMPXCHG_XBTS(BxInstruction_t *i)
{
  BX_INFO(("CMPXCHG_XBTS:"));
  UndefinedOpcode(i);
}

  void
bx_cpu_c::CMPXCHG_IBTS(BxInstruction_t *i)
{
  BX_INFO(("CMPXCHG_IBTS:"));
  UndefinedOpcode(i);
}


  void
bx_cpu_c::XADD_EdGd(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

    Bit32u op2_32, op1_32, sum_32;

    /* XADD dst(r/m), src(r)
     * temp <-- src + dst         | sum = op2 + op1
     * src  <-- dst               | op2 = op1
     * dst  <-- tmp               | op1 = sum
     */

    /* op2 is a register, i->rm_addr is an index of a register */
    op2_32 = BX_READ_32BIT_REG(i->nnn);

    /* op1 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    sum_32 = op1_32 + op2_32;

    /* now write sum back to destination */
    if (i->mod == 0xc0) {
      // and write destination into source
      // Note: if both op1 & op2 are registers, the last one written
      //       should be the sum, as op1 & op2 may be the same register.
      //       For example:  XADD AL, AL
      BX_WRITE_32BIT_REG(i->nnn, op1_32);
      BX_WRITE_32BIT_REG(i->rm, sum_32);
      }
    else {
      write_RMW_virtual_dword(sum_32);
      /* and write destination into source */
      BX_WRITE_32BIT_REG(i->nnn, op1_32);
      }


    SET_FLAGS_OSZAPC_32(op1_32, op2_32, sum_32, BX_INSTR_XADD32);
#else

#endif
}



  void
bx_cpu_c::ADD_EdId(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, sum_32;

    op2_32 = i->Id;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    sum_32 = op1_32 + op2_32;

    /* now write sum back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, sum_32);
      }
    else {
      write_RMW_virtual_dword(sum_32);
      }

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, sum_32, BX_INSTR_ADD32);
}

  void
bx_cpu_c::ADC_EdId(BxInstruction_t *i)
{
  Boolean temp_CF;

  temp_CF = get_CF();

    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, sum_32;

    op2_32 = i->Id;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    sum_32 = op1_32 + op2_32 + temp_CF;

    /* now write sum back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, sum_32);
      }
    else {
      write_RMW_virtual_dword(sum_32);
      }

    SET_FLAGS_OSZAPC_32_CF(op1_32, op2_32, sum_32, BX_INSTR_ADC32,
                              temp_CF);
}


  void
bx_cpu_c::SUB_EdId(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, diff_32;

    op2_32 = i->Id;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    diff_32 = op1_32 - op2_32;

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, diff_32);
      }
    else {
      write_RMW_virtual_dword(diff_32);
      }

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, diff_32, BX_INSTR_SUB32);
}

  void
bx_cpu_c::CMP_EdId(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op2_32, op1_32, diff_32;

    op2_32 = i->Id;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    diff_32 = op1_32 - op2_32;

    SET_FLAGS_OSZAPC_32(op1_32, op2_32, diff_32, BX_INSTR_CMP32);
}




  void
bx_cpu_c::NEG_Ed(BxInstruction_t *i)
{
    /* for 32 bit operand size mode */
    Bit32u op1_32, diff_32;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    diff_32 = 0 - op1_32;

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, diff_32);
      }
    else {
      write_RMW_virtual_dword(diff_32);
      }

    SET_FLAGS_OSZAPC_32(op1_32, 0, diff_32, BX_INSTR_NEG32);
}


  void
bx_cpu_c::INC_Ed(BxInstruction_t *i)
{
    Bit32u op1_32;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    op1_32++;

    /* now write sum back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, op1_32);
      }
    else {
      write_RMW_virtual_dword(op1_32);
      }

    SET_FLAGS_OSZAP_32(0, 0, op1_32, BX_INSTR_INC32);
}


  void
bx_cpu_c::DEC_Ed(BxInstruction_t *i)
{
    Bit32u op1_32;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    op1_32--;

    /* now write sum back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, op1_32);
      }
    else {
      write_RMW_virtual_dword(op1_32);
      }

    SET_FLAGS_OSZAP_32(0, 0, op1_32, BX_INSTR_DEC32);
}


  void
bx_cpu_c::CMPXCHG_EdGd(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

    Bit32u op2_32, op1_32, diff_32;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    diff_32 = EAX - op1_32;

    SET_FLAGS_OSZAPC_32(EAX, op1_32, diff_32, BX_INSTR_CMP32);

    if (diff_32 == 0) {  // if accumulator == dest
      // ZF = 1
      set_ZF(1);
      // dest <-- src
      op2_32 = BX_READ_32BIT_REG(i->nnn);

      if (i->mod == 0xc0) {
        BX_WRITE_32BIT_REG(i->rm, op2_32);
        }
      else {
        write_RMW_virtual_dword(op2_32);
        }
      }
    else {
      // ZF = 0
      set_ZF(0);
      // accumulator <-- dest
      EAX = op1_32;
      }
#else
  BX_PANIC(("CMPXCHG_EdGd:"));
#endif
}

  void
bx_cpu_c::CMPXCHG8B(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 5) || (BX_CPU_LEVEL_HACKED >= 5)

    Bit32u op1_64_lo, op1_64_hi, diff;

    if (i->mod == 0xc0) {
      BX_INFO(("CMPXCHG8B: dest is reg: #UD"));
      UndefinedOpcode(i);
      }

    /* pointer, segment address pair */
    read_virtual_dword(i->seg, i->rm_addr, &op1_64_lo);
    read_RMW_virtual_dword(i->seg, i->rm_addr + 4, &op1_64_hi);

    diff = EAX - op1_64_lo;
    diff |= EDX - op1_64_hi;

//     SET_FLAGS_OSZAPC_32(EAX, op1_32, diff_32, BX_INSTR_CMP32);

    if (diff == 0) {  // if accumulator == dest
      // ZF = 1
      set_ZF(1);
      // dest <-- src
      write_RMW_virtual_dword(ECX);
      write_virtual_dword(i->seg, i->rm_addr, &EBX);
      }
    else {
      // ZF = 0
      set_ZF(0);
      // accumulator <-- dest
      EAX = op1_64_lo;
      EDX = op1_64_hi;
      }
  
#else
  BX_INFO(("CMPXCHG8B: not implemented yet"));
  UndefinedOpcode(i);
#endif
}
