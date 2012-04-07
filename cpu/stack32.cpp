/////////////////////////////////////////////////////////////////////////
// $Id: stack32.cc,v 1.8 2002/03/05 15:50:17 bdenney Exp $
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

#if BX_USE_CPU_SMF
#define this (BX_CPU(0))
#endif


  void
bx_cpu_c::POP_Ed(BxInstruction_t *i)
{
  Bit32u val32;

  pop_32(&val32);

  if (i->mod == 0xc0) {
    BX_WRITE_32BIT_REG(i->rm, val32);
    }
  else {
    // Note: there is one little weirdism here.  When 32bit addressing
    // is used, it is possible to use ESP in the modrm addressing.
    // If used, the value of ESP after the pop is used to calculate
    // the address.
    if (i->as_32 && (i->mod!=0xc0) && (i->rm==4) && (i->base==4)) {
      // call method on bx_cpu_c object
      i->ResolveModrm(i);
      }
    write_virtual_dword(i->seg, i->rm_addr, &val32);
    }
}

  void
bx_cpu_c::PUSH_ERX(BxInstruction_t *i)
{
  push_32(bx_cpu. gen_reg[i->b1 & 0x07].erx);
}

  void
bx_cpu_c::POP_ERX(BxInstruction_t *i)
{
  Bit32u erx;

  pop_32(&erx);
  bx_cpu. gen_reg[i->b1 & 0x07].erx = erx;
}


  void
bx_cpu_c::PUSH_CS(BxInstruction_t *i)
{
  if (i->os_32)
    push_32(bx_cpu. sregs[BX_SEG_REG_CS].selector.value);
  else
    push_16(bx_cpu. sregs[BX_SEG_REG_CS].selector.value);
}
  void
bx_cpu_c::PUSH_DS(BxInstruction_t *i)
{
  if (i->os_32)
    push_32(bx_cpu. sregs[BX_SEG_REG_DS].selector.value);
  else
    push_16(bx_cpu. sregs[BX_SEG_REG_DS].selector.value);
}
  void
bx_cpu_c::PUSH_ES(BxInstruction_t *i)
{
  if (i->os_32)
    push_32(bx_cpu. sregs[BX_SEG_REG_ES].selector.value);
  else
    push_16(bx_cpu. sregs[BX_SEG_REG_ES].selector.value);
}
  void
bx_cpu_c::PUSH_FS(BxInstruction_t *i)
{
  if (i->os_32)
    push_32(bx_cpu. sregs[BX_SEG_REG_FS].selector.value);
  else
    push_16(bx_cpu. sregs[BX_SEG_REG_FS].selector.value);
}
  void
bx_cpu_c::PUSH_GS(BxInstruction_t *i)
{
  if (i->os_32)
    push_32(bx_cpu. sregs[BX_SEG_REG_GS].selector.value);
  else
    push_16(bx_cpu. sregs[BX_SEG_REG_GS].selector.value);
}
  void
bx_cpu_c::PUSH_SS(BxInstruction_t *i)
{
  if (i->os_32)
    push_32(bx_cpu. sregs[BX_SEG_REG_SS].selector.value);
  else
    push_16(bx_cpu. sregs[BX_SEG_REG_SS].selector.value);
}


  void
bx_cpu_c::POP_DS(BxInstruction_t *i)
{
  if (i->os_32) {
    Bit32u ds;
    pop_32(&ds);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_DS], (Bit16u) ds);
    }
  else {
    Bit16u ds;
    pop_16(&ds);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_DS], ds);
    }
}
  void
bx_cpu_c::POP_ES(BxInstruction_t *i)
{
  if (i->os_32) {
    Bit32u es;
    pop_32(&es);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_ES], (Bit16u) es);
    }
  else {
    Bit16u es;
    pop_16(&es);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_ES], es);
    }
}
  void
bx_cpu_c::POP_FS(BxInstruction_t *i)
{
  if (i->os_32) {
    Bit32u fs;
    pop_32(&fs);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_FS], (Bit16u) fs);
    }
  else {
    Bit16u fs;
    pop_16(&fs);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_FS], fs);
    }
}
  void
bx_cpu_c::POP_GS(BxInstruction_t *i)
{
  if (i->os_32) {
    Bit32u gs;
    pop_32(&gs);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_GS], (Bit16u) gs);
    }
  else {
    Bit16u gs;
    pop_16(&gs);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_GS], gs);
    }
}
  void
bx_cpu_c::POP_SS(BxInstruction_t *i)
{
  if (i->os_32) {
    Bit32u ss;
    pop_32(&ss);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_SS], (Bit16u) ss);
    }
  else {
    Bit16u ss;
    pop_16(&ss);
    load_seg_reg(&bx_cpu. sregs[BX_SEG_REG_SS], ss);
    }

  // POP SS inhibits interrupts, debug exceptions and single-step
  // trap exceptions until the execution boundary following the
  // next instruction is reached.
  // Same code as MOV_SwEw()
  bx_cpu. inhibit_mask |=
    BX_INHIBIT_INTERRUPTS | BX_INHIBIT_DEBUG;
  bx_cpu. async_event = 1;
}


  void
bx_cpu_c::PUSHAD32(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("PUSHAD: not supported on an 8086"));
#else
  Bit32u temp_ESP;
  Bit32u esp;

  if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    temp_ESP = ESP;
  else
    temp_ESP = SP;


    if (protected_mode()) {
      if ( !can_push(&bx_cpu. sregs[BX_SEG_REG_SS].cache, temp_ESP, 32) ) {
        BX_PANIC(("PUSHAD(): stack doesn't have enough room!"));
        exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }
    else {
      if (temp_ESP < 32)
        BX_PANIC(("pushad: eSP < 32"));
      }

    esp = ESP;

    /* ??? optimize this by using virtual write, all checks passed */
    push_32(EAX);
    push_32(ECX);
    push_32(EDX);
    push_32(EBX);
    push_32(esp);
    push_32(EBP);
    push_32(ESI);
    push_32(EDI);
#endif
}

  void
bx_cpu_c::POPAD32(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("POPAD not supported on an 8086"));
#else /* 286+ */
    Bit32u edi, esi, ebp, etmp, ebx, edx, ecx, eax;

    if (protected_mode()) {
      if ( !can_pop(32) ) {
        BX_PANIC(("pop_ad: not enough bytes on stack"));
        exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }

    /* ??? optimize this */
    pop_32(&edi);
    pop_32(&esi);
    pop_32(&ebp);
    pop_32(&etmp); /* value for ESP discarded */
    pop_32(&ebx);
    pop_32(&edx);
    pop_32(&ecx);
    pop_32(&eax);

    EDI = edi;
    ESI = esi;
    EBP = ebp;
    EBX = ebx;
    EDX = edx;
    ECX = ecx;
    EAX = eax;
#endif
}

  void
bx_cpu_c::PUSH_Id(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("PUSH_Iv: not supported on 8086!"));
#else

    Bit32u imm32;

    imm32 = i->Id;

    push_32(imm32);
#endif
}

  void
bx_cpu_c::PUSH_Ed(BxInstruction_t *i)
{
    Bit32u op1_32;

    /* op1_32 is a register or memory reference */
    if (i->mod == 0xc0) {
      op1_32 = BX_READ_32BIT_REG(i->rm);
      }
    else {
      /* pointer, segment address pair */
      read_virtual_dword(i->seg, i->rm_addr, &op1_32);
      }

    push_32(op1_32);
}


  void
bx_cpu_c::ENTER_IwIb(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("ENTER_IwIb: not supported by 8086!"));
#else
  Bit32u frame_ptr32;
  Bit16u frame_ptr16;
  Bit8u level;
  static Bit8u first_time = 1;

  level = i->Ib2;

  invalidate_prefetch_q();

  level %= 32;
/* ??? */
  if (first_time && level>0) {
    BX_ERROR(("enter() with level > 0. The emulation of this instruction may not be complete.  This warning will be printed only once per bochs run."));
    first_time = 0;
  }
//if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b && i->os_32==0) {
//  BX_INFO(("enter(): stacksize!=opsize: I'm unsure of the code for this"));
//  BX_PANIC(("         The Intel manuals are a mess on this one!"));
//  }

  if ( protected_mode() ) {
    Bit32u bytes_to_push, temp_ESP;

    if (level == 0) {
      if (i->os_32)
        bytes_to_push = 4 + i->Iw;
      else
        bytes_to_push = 2 + i->Iw;
      }
    else { /* level > 0 */
      if (i->os_32)
        bytes_to_push = 4 + (level-1)*4 + 4 + i->Iw;
      else
        bytes_to_push = 2 + (level-1)*2 + 2 + i->Iw;
      }
    if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
      temp_ESP = ESP;
    else
      temp_ESP = SP;
    if ( !can_push(&bx_cpu. sregs[BX_SEG_REG_SS].cache, temp_ESP, bytes_to_push) ) {
      BX_PANIC(("ENTER: not enough room on stack!"));
      exception(BX_SS_EXCEPTION, 0, 0);
      }
    }

  if (i->os_32)
    push_32(EBP);
  else
    push_16(BP);

  // can just do frame_ptr32 = ESP for either case ???
  if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    frame_ptr32 = ESP;
  else
    frame_ptr32 = SP;

  if (level > 0) {
    /* do level-1 times */
    while (--level) {
      if (i->os_32) {
        Bit32u temp32;

        if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
          EBP -= 4;
          read_virtual_dword(BX_SEG_REG_SS, EBP, &temp32);
          ESP -= 4;
          write_virtual_dword(BX_SEG_REG_SS, ESP, &temp32);
          }
        else { /* 16bit stacksize */
          BP -= 4;
          read_virtual_dword(BX_SEG_REG_SS, BP, &temp32);
          SP -= 4;
          write_virtual_dword(BX_SEG_REG_SS, SP, &temp32);
          }
        }
      else { /* 16bit opsize */
        Bit16u temp16;

        if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
          EBP -= 2;
          read_virtual_word(BX_SEG_REG_SS, EBP, &temp16);
          ESP -= 2;
          write_virtual_word(BX_SEG_REG_SS, ESP, &temp16);
          }
        else { /* 16bit stacksize */
          BP -= 2;
          read_virtual_word(BX_SEG_REG_SS, BP, &temp16);
          SP -= 2;
          write_virtual_word(BX_SEG_REG_SS, SP, &temp16);
          }
        }
      } /* while (--level) */

    /* push(frame pointer) */
    if (i->os_32) {
      if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
        ESP -= 4;
        write_virtual_dword(BX_SEG_REG_SS, ESP, &frame_ptr32);
        }
      else {
        SP -= 4;
        write_virtual_dword(BX_SEG_REG_SS, SP, &frame_ptr32);
        }
      }
    else { /* 16bit opsize */
      if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
        frame_ptr16 = frame_ptr32;
        ESP -= 2;
        write_virtual_word(BX_SEG_REG_SS, ESP, &frame_ptr16);
        }
      else {
        frame_ptr16 = frame_ptr32;
        SP -= 2;
        write_virtual_word(BX_SEG_REG_SS, SP, &frame_ptr16);
        }
      }
    } /* if (level > 0) ... */

  if (i->os_32)
    EBP = frame_ptr32;
  else
    BP = frame_ptr32;

  if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
    ESP = ESP - i->Iw;
    }
  else { /* 16bit stack */
    SP = SP - i->Iw;
    }
#endif
}

  void
bx_cpu_c::LEAVE(BxInstruction_t *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("LEAVE: not supported by 8086!"));
#else
  Bit32u temp_EBP;


  invalidate_prefetch_q();

#if BX_CPU_LEVEL >= 3
  if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    temp_EBP = EBP;
  else
#endif
    temp_EBP = BP;

  if ( protected_mode() ) {
    if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.c_ed) { /* expand up */
      if (temp_EBP <= bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.limit_scaled) {
        BX_PANIC(("LEAVE: BP > bx_cpu. sregs[BX_SEG_REG_SS].limit"));
        exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }
    else { /* normal */
      if (temp_EBP > bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.limit_scaled) {
        BX_PANIC(("LEAVE: BP > bx_cpu. sregs[BX_SEG_REG_SS].limit"));
        exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }
    }


  // delete frame
#if BX_CPU_LEVEL >= 3
  if (bx_cpu. sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    ESP = EBP;
  else
#endif
    SP = BP;

  // restore frame pointer
#if BX_CPU_LEVEL >= 3
  if (i->os_32) {
    Bit32u temp32;

    pop_32(&temp32);
    EBP = temp32;
    }
  else
#endif
    {
    Bit16u temp16;

    pop_16(&temp16);
    BP = temp16;
    }
#endif
}
