/////////////////////////////////////////////////////////////////////////
// $Id: bit.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
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
bx_cpu_c::SETO_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETO: not available on < 386"));
#else
  Bit8u result_8;


  if (get_OF())
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETNO_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETNO: not available on < 386"));
#else
  Bit8u result_8;


  if (get_OF()==0)
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETB_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETB: not available on < 386"));
#else
  Bit8u result_8;


  if (get_CF())
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETNB_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETNB: not available on < 386"));
#else
  Bit8u result_8;


  if (get_CF()==0)
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETZ_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETZ: not available on < 386"));
#else
  Bit8u result_8;


  if (get_ZF())
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETNZ_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETNZ: not available on < 386"));
#else
  Bit8u result_8;


  if (get_ZF()==0)
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETBE_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETBE: not available on < 386"));
#else
  Bit8u result_8;


  if (get_CF() || get_ZF())
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETNBE_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETNBE: not available on < 386"));
#else
  Bit8u result_8;


  if ((get_CF()==0) && (get_ZF()==0))
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETS_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETS: not available on < 386"));
#else
  Bit8u result_8;


  if (get_SF())
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETNS_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETNL: not available on < 386"));
#else
  Bit8u result_8;


  if (get_SF()==0)
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETP_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETP: not available on < 386"));
#else
  Bit8u result_8;


  if (get_PF())
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETNP_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETNP: not available on < 386"));
#else
  Bit8u result_8;


  if (get_PF() == 0)
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETL_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETL: not available on < 386"));
#else
  Bit8u result_8;


  if (get_SF() != get_OF())
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETNL_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETNL: not available on < 386"));
#else
  Bit8u result_8;


  if (get_SF() == get_OF())
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETLE_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETLE: not available on < 386"));
#else
  Bit8u result_8;


  if (get_ZF() || (get_SF()!=get_OF()))
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}

  void
bx_cpu_c::SETNLE_Eb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("SETNLE: not available on < 386"));
#else
  Bit8u result_8;


  if ((get_ZF()==0) && (get_SF()==get_OF()))
    result_8 = 1;
  else
    result_8 = 0;

  /* now write result back to destination */
  if (i->mod == 0xc0) {
    BX_WRITE_8BIT_REG(i->rm, result_8);
    }
  else {
    write_virtual_byte(i->seg, i->rm_addr, &result_8);
    }
#endif
}


  void
bx_cpu_c::BSF_GvEv(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BSF_GvEv(): not supported on < 386"));
#else


  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32;

    /* op2_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op2_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op2_32);
      }

    if (op2_32 == 0) {
      set_ZF(1);
      /* op1_32 undefined */
      return;
      }

    op1_32 = 0;
    while ( (op2_32 & 0x01) == 0 ) {
      op1_32++;
      op2_32 >>= 1;
      }
    set_ZF(0);

    /* now write result back to destination */
    BX_WRITE_32BIT_REG(i->nnn, op1_32);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16, op2_16;

    /* op2_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op2_16 = BX_READ_16BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_word(i->seg, i->rm_addr, &op2_16);
      }

    if (op2_16 == 0) {
      set_ZF(1);
      /* op1_16 undefined */
      return;
      }

    op1_16 = 0;
    while ( (op2_16 & 0x01) == 0 ) {
      op1_16++;
      op2_16 >>= 1;
      }
    set_ZF(0);

    /* now write result back to destination */
    BX_WRITE_16BIT_REG(i->nnn, op1_16);
    }
#endif
}

  void
bx_cpu_c::BSR_GvEv(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BSR_GvEv(): not supported on < 386"));
#else


  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32;

    /* op2_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op2_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op2_32);
      }

    if (op2_32 == 0) {
      set_ZF(1);
      /* op1_32 undefined */
      return;
      }

    op1_32 = 31;
    while ( (op2_32 & 0x80000000) == 0 ) {
      op1_32--;
      op2_32 <<= 1;
      }
    set_ZF(0);

    /* now write result back to destination */
    BX_WRITE_32BIT_REG(i->nnn, op1_32);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16, op2_16;

    /* op2_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op2_16 = BX_READ_16BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_word(i->seg, i->rm_addr, &op2_16);
      }

    if (op2_16 == 0) {
      set_ZF(1);
      /* op1_16 undefined */
      return;
      }

    op1_16 = 15;
    while ( (op2_16 & 0x8000) == 0 ) {
      op1_16--;
      op2_16 <<= 1;
      }
    set_ZF(0);

    /* now write result back to destination */
    BX_WRITE_16BIT_REG(i->nnn, op1_16);
    }
#endif
}


  void
bx_cpu_c::BSWAP_EAX(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

  Bit32u eax, b0, b1, b2, b3;

  eax = EAX;
  b0  = eax & 0xff; eax >>= 8;
  b1  = eax & 0xff; eax >>= 8;
  b2  = eax & 0xff; eax >>= 8;
  b3  = eax;

  EAX = (b0<<24) | (b1<<16) | (b2<<8) | b3;
#else
  BX_PANIC(("BSWAP_EAX: not implemented CPU <= 3"));
#endif
}

  void
bx_cpu_c::BSWAP_ECX(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

  Bit32u ecx, b0, b1, b2, b3;

  ecx = ECX;
  b0  = ecx & 0xff; ecx >>= 8;
  b1  = ecx & 0xff; ecx >>= 8;
  b2  = ecx & 0xff; ecx >>= 8;
  b3  = ecx;

  ECX = (b0<<24) | (b1<<16) | (b2<<8) | b3;
#else
  BX_PANIC(("BSWAP_ECX: not implemented CPU <= 3"));
#endif
}
  void
bx_cpu_c::BSWAP_EDX(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

  Bit32u edx, b0, b1, b2, b3;

  edx = EDX;
  b0  = edx & 0xff; edx >>= 8;
  b1  = edx & 0xff; edx >>= 8;
  b2  = edx & 0xff; edx >>= 8;
  b3  = edx;

  EDX = (b0<<24) | (b1<<16) | (b2<<8) | b3;
#else
  BX_PANIC(("BSWAP_EDX: not implemented CPU <= 3"));
#endif
}
  void
bx_cpu_c::BSWAP_EBX(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

  Bit32u ebx, b0, b1, b2, b3;

  ebx = EBX;
  b0  = ebx & 0xff; ebx >>= 8;
  b1  = ebx & 0xff; ebx >>= 8;
  b2  = ebx & 0xff; ebx >>= 8;
  b3  = ebx;

  EBX = (b0<<24) | (b1<<16) | (b2<<8) | b3;
#else
  BX_PANIC(("BSWAP_EBX: not implemented CPU <= 3"));
#endif
}
  void
bx_cpu_c::BSWAP_ESP(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

  Bit32u esp, b0, b1, b2, b3;

  esp = ESP;
  b0  = esp & 0xff; esp >>= 8;
  b1  = esp & 0xff; esp >>= 8;
  b2  = esp & 0xff; esp >>= 8;
  b3  = esp;

  ESP = (b0<<24) | (b1<<16) | (b2<<8) | b3;
#else
  BX_PANIC(("BSWAP_ESP: not implemented CPU <= 3"));
#endif
}
  void
bx_cpu_c::BSWAP_EBP(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

  Bit32u ebp, b0, b1, b2, b3;

  ebp = EBP;
  b0  = ebp & 0xff; ebp >>= 8;
  b1  = ebp & 0xff; ebp >>= 8;
  b2  = ebp & 0xff; ebp >>= 8;
  b3  = ebp;

  EBP = (b0<<24) | (b1<<16) | (b2<<8) | b3;
#else
  BX_PANIC(("BSWAP_EBP: not implemented CPU <= 3"));
#endif
}
  void
bx_cpu_c::BSWAP_ESI(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

  Bit32u esi, b0, b1, b2, b3;

  esi = ESI;
  b0  = esi & 0xff; esi >>= 8;
  b1  = esi & 0xff; esi >>= 8;
  b2  = esi & 0xff; esi >>= 8;
  b3  = esi;

  ESI = (b0<<24) | (b1<<16) | (b2<<8) | b3;
#else
  BX_PANIC(("BSWAP_ESI: not implemented CPU <= 3"));
#endif
}
  void
bx_cpu_c::BSWAP_EDI(BxInstruction_t *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

  Bit32u edi, b0, b1, b2, b3;

  edi = EDI;
  b0  = edi & 0xff; edi >>= 8;
  b1  = edi & 0xff; edi >>= 8;
  b2  = edi & 0xff; edi >>= 8;
  b3  = edi;

  EDI = (b0<<24) | (b1<<16) | (b2<<8) | b3;
#else
  BX_PANIC(("BSWAP_EDI: not implemented CPU <= 3"));
#endif
}


  void
bx_cpu_c::BT_EvGv(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BT_EvGv: not available on <386"));
#else
  Bit32u op1_addr;

  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, index;
    Bit32s displacement32;

    /* op2_32 is a register, op2_addr is an index of a register */
    op2_32 = BX_READ_32BIT_REG(i->nnn);

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      op2_32 &= 0x1f;
      set_CF((op1_32 >> op2_32) & 0x01);
      return;
      }

    index = op2_32 & 0x1f;
    displacement32 = ((Bit32s) (op2_32&0xffffffe0)) / 32;
    op1_addr = i->rm_addr + 4 * displacement32;

    /* pointer, segment address pair */
    read_virtual_dword(i->seg, op1_addr, &op1_32);

    set_CF((op1_32 >> index) & 0x01);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16, op2_16, index;
    Bit32s displacement32;

    /* op2_16 is a register, op2_addr is an index of a register */
    op2_16 = BX_READ_16BIT_REG(i->nnn);

    /* op1_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_16 = BX_READ_16BIT_REG(i->rm);
      op2_16 &= 0x0f;
      set_CF((op1_16 >> op2_16) & 0x01);
      return;
      }

    index = op2_16 & 0x0f;
    displacement32 = ((Bit16s) (op2_16&0xfff0)) / 16;
    op1_addr = i->rm_addr + 2 * displacement32;

    /* pointer, segment address pair */
    read_virtual_word(i->seg, op1_addr, &op1_16);

    set_CF((op1_16 >> index) & 0x01);
    }
#endif
}

  void
bx_cpu_c::BTS_EvGv(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BTS_EvGv: not available on <386"));
#else
  Bit32u op1_addr;

  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, bit_i, index;
    Bit32s displacement32;

    /* op2_32 is a register, op2_addr is an index of a register */
    op2_32 = BX_READ_32BIT_REG(i->nnn);

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      op2_32 &= 0x1f;
      set_CF((op1_32 >> op2_32) & 0x01);
      op1_32 |= (((Bit32u) 1) << op2_32);

      /* now write diff back to destination */
      BX_WRITE_32BIT_REG(i->rm, op1_32);
      return;
      }

    index = op2_32 & 0x1f;
    displacement32 = ((Bit32s) (op2_32&0xffffffe0)) / 32;
    op1_addr = i->rm_addr + 4 * displacement32;

    /* pointer, segment address pair */
    read_RMW_virtual_dword(i->seg, op1_addr, &op1_32);

    bit_i = (op1_32 >> index) & 0x01;
    op1_32 |= (((Bit32u) 1) << index);

    write_RMW_virtual_dword(op1_32);

    set_CF(bit_i);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16, op2_16, bit_i, index;
    Bit32s displacement32;

    /* op2_16 is a register, op2_addr is an index of a register */
    op2_16 = BX_READ_16BIT_REG(i->nnn);

    /* op1_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_16 = BX_READ_16BIT_REG(i->rm);
      op2_16 &= 0x0f;
      set_CF((op1_16 >> op2_16) & 0x01);
      op1_16 |= (((Bit16u) 1) << op2_16);

      /* now write diff back to destination */
      BX_WRITE_16BIT_REG(i->rm, op1_16);
      return;
      }

    index = op2_16 & 0x0f;
    displacement32 = ((Bit16s) (op2_16&0xfff0)) / 16;
    op1_addr = i->rm_addr + 2 * displacement32;

    /* pointer, segment address pair */
    read_RMW_virtual_word(i->seg, op1_addr, &op1_16);

    bit_i = (op1_16 >> index) & 0x01;
    op1_16 |= (((Bit16u) 1) << index);

    write_RMW_virtual_word(op1_16);

    set_CF(bit_i);
    }
#endif
}

  void
bx_cpu_c::BTR_EvGv(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BTR_EvGv: not available on <386"));
#else
  Bit32u op1_addr;


  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, index, temp_cf;
    Bit32s displacement32;

    /* op2_32 is a register, op2_addr is an index of a register */
    op2_32 = BX_READ_32BIT_REG(i->nnn);

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      op2_32 &= 0x1f;
      set_CF((op1_32 >> op2_32) & 0x01);
      op1_32 &= ~(((Bit32u) 1) << op2_32);

      /* now write diff back to destination */
      BX_WRITE_32BIT_REG(i->rm, op1_32);
      return;
      }

    index = op2_32 & 0x1f;
    displacement32 = ((Bit32s) (op2_32&0xffffffe0)) / 32;
    op1_addr = i->rm_addr + 4 * displacement32;

    /* pointer, segment address pair */
    read_RMW_virtual_dword(i->seg, op1_addr, &op1_32);

    temp_cf = (op1_32 >> index) & 0x01;
    op1_32 &= ~(((Bit32u) 1) << index);

    /* now write back to destination */
    write_RMW_virtual_dword(op1_32);

    set_CF(temp_cf);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16, op2_16, index, temp_cf;
    Bit32s displacement32;

    /* op2_16 is a register, op2_addr is an index of a register */
    op2_16 = BX_READ_16BIT_REG(i->nnn);

    /* op1_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_16 = BX_READ_16BIT_REG(i->rm);
      op2_16 &= 0x0f;
      set_CF((op1_16 >> op2_16) & 0x01);
      op1_16 &= ~(((Bit16u) 1) << op2_16);

      /* now write diff back to destination */
      BX_WRITE_16BIT_REG(i->rm, op1_16);
      return;
      }

    index = op2_16 & 0x0f;
    displacement32 = ((Bit16s) (op2_16&0xfff0)) / 16;
    op1_addr = i->rm_addr + 2 * displacement32;

    /* pointer, segment address pair */
    read_RMW_virtual_word(i->seg, op1_addr, &op1_16);

    temp_cf = (op1_16 >> index) & 0x01;
    op1_16 &= ~(((Bit16u) 1) << index);

    /* now write back to destination */
    write_RMW_virtual_word(op1_16);

    set_CF(temp_cf);
    }
#endif
}

  void
bx_cpu_c::BTC_EvGv(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BTC_EvGv: not available on <386"));
#else
  Bit32u op1_addr;

  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32, op2_32, index_32, temp_CF;
    Bit32s displacement32;

    op2_32 = BX_READ_32BIT_REG(i->nnn);
    index_32 = op2_32 & 0x1f;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      op1_addr = 0; // keep compiler happy
      }
    else {
      displacement32 = ((Bit32s) (op2_32 & 0xffffffe0)) / 32;
      op1_addr = i->rm_addr + 4 * displacement32;
      read_RMW_virtual_dword(i->seg, op1_addr, &op1_32);
      }

    temp_CF = (op1_32 >> index_32) & 0x01;
    op1_32 &= ~(((Bit32u) 1) << index_32);  /* clear out bit */
    op1_32 |= (((Bit32u) !temp_CF) << index_32); /* set to complement */

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, op1_32);
      }
    else {
      write_RMW_virtual_dword(op1_32);
      }
    set_CF(temp_CF);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16, op2_16, index_16, temp_CF;
    Bit16s displacement16;

    op2_16 = BX_READ_16BIT_REG(i->nnn);
    index_16 = op2_16 & 0x0f;

    /* op1_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_16 = BX_READ_16BIT_REG(i->rm);
      op1_addr = 0; // keep compiler happy
      }
    else {
      displacement16 = ((Bit16s) (op2_16 & 0xfff0)) / 16;
      op1_addr = i->rm_addr + 2 * displacement16;
      read_RMW_virtual_word(i->seg, op1_addr, &op1_16);
      }

    temp_CF = (op1_16 >> index_16) & 0x01;
    op1_16 &= ~(((Bit16u) 1) << index_16);  /* clear out bit */
    op1_16 |= (((Bit16u) !temp_CF) << index_16); /* set to complement */

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_16BIT_REG(i->rm, op1_16);
      }
    else {
      write_RMW_virtual_word(op1_16);
      }
    set_CF(temp_CF);
    }
#endif
}

  void
bx_cpu_c::BT_EvIb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BT_EvIb: not available on <386"));
#else

  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32;
    Bit8u  op2_8;

    op2_8 = i->Ib;
    op2_8 %= 32;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    set_CF((op1_32 >> op2_8) & 0x01);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16;
    Bit8u  op2_8;


    op2_8 = i->Ib;
    op2_8 %= 16;

    /* op1_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_16 = BX_READ_16BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_word(i->seg, i->rm_addr, &op1_16);
      }

    set_CF((op1_16 >> op2_8) & 0x01);
    }
#endif
}

  void
bx_cpu_c::BTS_EvIb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BTS_EvIb: not available on <386"));
#else

  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32, temp_CF;
    Bit8u  op2_8;

    op2_8 = i->Ib;
    op2_8 %= 32;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    temp_CF = (op1_32 >> op2_8) & 0x01;
    op1_32 |= (((Bit32u) 1) << op2_8);

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, op1_32);
      }
    else {
      write_RMW_virtual_dword(op1_32);
      }
    set_CF(temp_CF);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16, temp_CF;
    Bit8u  op2_8;


    op2_8 = i->Ib;
    op2_8 %= 16;

    /* op1_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_16 = BX_READ_16BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_word(i->seg, i->rm_addr, &op1_16);
      }

    temp_CF = (op1_16 >> op2_8) & 0x01;
    op1_16 |= (((Bit16u) 1) << op2_8);

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_16BIT_REG(i->rm, op1_16);
      }
    else {
      write_RMW_virtual_word(op1_16);
      }
    set_CF(temp_CF);
    }
#endif
}

  void
bx_cpu_c::BTC_EvIb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BTC_EvIb: not available on <386"));
#else

  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32, temp_CF;
    Bit8u  op2_8;

    op2_8 = i->Ib;
    op2_8 %= 32;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    temp_CF = (op1_32 >> op2_8) & 0x01;

    op1_32 &= ~(((Bit32u) 1) << op2_8);  /* clear out bit */
    op1_32 |= (((Bit32u) !temp_CF) << op2_8); /* set to complement */

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, op1_32);
      }
    else {
      write_RMW_virtual_dword(op1_32);
      }
    set_CF(temp_CF);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16, temp_CF;
    Bit8u  op2_8;


    op2_8 = i->Ib;
    op2_8 %= 16;

    /* op1_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_16 = BX_READ_16BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_word(i->seg, i->rm_addr, &op1_16);
      }

    temp_CF = (op1_16 >> op2_8) & 0x01;
    op1_16 &= ~(((Bit16u) 1) << op2_8);  /* clear out bit */
    op1_16 |= (((Bit16u) !temp_CF) << op2_8); /* set to complement */

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_16BIT_REG(i->rm, op1_16);
      }
    else {
      write_RMW_virtual_word(op1_16);
      }
    set_CF(temp_CF);
    }
#endif
}

  void
bx_cpu_c::BTR_EvIb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 3
  BX_PANIC(("BTR_EvIb: not available on <386"));
#else

  if (i->os_32) { /* 32 bit operand size mode */
    /* for 32 bit operand size mode */
    Bit32u op1_32, temp_CF;
    Bit8u  op2_8;

    op2_8 = i->Ib;
    op2_8 %= 32;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    temp_CF = (op1_32 >> op2_8) & 0x01;
    op1_32 &= ~(((Bit32u) 1) << op2_8);

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_32BIT_REG(i->rm, op1_32);
      }
    else {
      write_RMW_virtual_dword(op1_32);
      }
    set_CF(temp_CF);
    }
  else { /* 16 bit operand size mode */
    Bit16u op1_16, temp_CF;
    Bit8u  op2_8;


    op2_8 = i->Ib;
    op2_8 %= 16;

    /* op1_16 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_16 = BX_READ_16BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_RMW_virtual_word(i->seg, i->rm_addr, &op1_16);
      }

    temp_CF = (op1_16 >> op2_8) & 0x01;
    op1_16 &= ~(((Bit16u) 1) << op2_8);

    /* now write diff back to destination */
    if (i->mod == 0xc0) {
      BX_WRITE_16BIT_REG(i->rm, op1_16);
      }
    else {
      write_RMW_virtual_word(op1_16);
      }
    set_CF(temp_CF);
    }
#endif
}
