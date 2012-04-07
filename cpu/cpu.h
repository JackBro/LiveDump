/////////////////////////////////////////////////////////////////////////
// $Id: cpu.h,v 1.17 2002/03/27 16:04:04 bdenney Exp $
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


#ifndef BX_CPU_H
#  define BX_CPU_H 1

#include <setjmp.h>

#include "cpu/lazy_flags.h"


#define BX_SREG_ES    0
#define BX_SREG_CS    1
#define BX_SREG_SS    2
#define BX_SREG_DS    3
#define BX_SREG_FS    4
#define BX_SREG_GS    5

// segment register encoding
#define BX_SEG_REG_ES    0
#define BX_SEG_REG_CS    1
#define BX_SEG_REG_SS    2
#define BX_SEG_REG_DS    3
#define BX_SEG_REG_FS    4
#define BX_SEG_REG_GS    5
#define BX_SEG_REG_NULL  8
#define BX_NULL_SEG_REG(seg) ((seg) & BX_SEG_REG_NULL)


#ifdef BX_LITTLE_ENDIAN
#define BX_REG8L_OFFSET 0
#define BX_REG8H_OFFSET 1
#define BX_REG16_OFFSET 0
#else // BX_BIG_ENDIAN
#define BX_REG8L_OFFSET 3
#define BX_REG8H_OFFSET 2
#define BX_REG16_OFFSET 2
#endif // ifdef BX_LITTLE_ENDIAN

#define BX_8BIT_REG_AL  0
#define BX_8BIT_REG_CL  1
#define BX_8BIT_REG_DL  2
#define BX_8BIT_REG_BL  3
#define BX_8BIT_REG_AH  4
#define BX_8BIT_REG_CH  5
#define BX_8BIT_REG_DH  6
#define BX_8BIT_REG_BH  7

#define BX_16BIT_REG_AX 0
#define BX_16BIT_REG_CX 1
#define BX_16BIT_REG_DX 2
#define BX_16BIT_REG_BX 3
#define BX_16BIT_REG_SP 4
#define BX_16BIT_REG_BP 5
#define BX_16BIT_REG_SI 6
#define BX_16BIT_REG_DI 7

#define BX_32BIT_REG_EAX 0
#define BX_32BIT_REG_ECX 1
#define BX_32BIT_REG_EDX 2
#define BX_32BIT_REG_EBX 3
#define BX_32BIT_REG_ESP 4
#define BX_32BIT_REG_EBP 5
#define BX_32BIT_REG_ESI 6
#define BX_32BIT_REG_EDI 7


#if defined(NEED_CPU_REG_SHORTCUTS)

/* WARNING: 
   Only bx_cpu_c member functions can use these shortcuts safely!
   Functions that use the shortcuts outside of bx_cpu_c might work 
   when BX_USE_CPU_SMF=1 but will fail when BX_USE_CPU_SMF=0
   (for example in SMP mode).
*/

// access to 8 bit general registers
#define AL (bx_cpu. gen_reg[0].word.byte.rl)
#define CL (bx_cpu. gen_reg[1].word.byte.rl)
#define DL (bx_cpu. gen_reg[2].word.byte.rl)
#define BL (bx_cpu. gen_reg[3].word.byte.rl)
#define AH (bx_cpu. gen_reg[0].word.byte.rh)
#define CH (bx_cpu. gen_reg[1].word.byte.rh)
#define DH (bx_cpu. gen_reg[2].word.byte.rh)
#define BH (bx_cpu. gen_reg[3].word.byte.rh)


// access to 16 bit general registers
#define AX (bx_cpu. gen_reg[0].word.rx)
#define CX (bx_cpu. gen_reg[1].word.rx)
#define DX (bx_cpu. gen_reg[2].word.rx)
#define BX (bx_cpu. gen_reg[3].word.rx)
#define SP (bx_cpu. gen_reg[4].word.rx)
#define BP (bx_cpu. gen_reg[5].word.rx)
#define SI (bx_cpu. gen_reg[6].word.rx)
#define DI (bx_cpu. gen_reg[7].word.rx)

// access to 16 bit instruction pointer
#define IP (* (Bit16u *) (((Bit8u *) &bx_cpu. eip) + BX_REG16_OFFSET))


// accesss to 32 bit general registers
#define EAX bx_cpu. gen_reg[0].erx
#define ECX bx_cpu. gen_reg[1].erx
#define EDX bx_cpu. gen_reg[2].erx
#define EBX bx_cpu. gen_reg[3].erx
#define ESP bx_cpu. gen_reg[4].erx
#define EBP bx_cpu. gen_reg[5].erx
#define ESI bx_cpu. gen_reg[6].erx
#define EDI bx_cpu. gen_reg[7].erx

// access to 32 bit instruction pointer
#define EIP bx_cpu. eip


#define BX_READ_8BIT_REG(index)  (((index) < 4) ? \
  (bx_cpu. gen_reg[index].word.byte.rl) : \
  (bx_cpu. gen_reg[(index)-4].word.byte.rh))
#define BX_READ_16BIT_REG(index) (bx_cpu. gen_reg[index].word.rx)
#define BX_READ_32BIT_REG(index) (bx_cpu. gen_reg[index].erx)

#define BX_READ_16BIT_BASE_REG(var, index) {\
  var = *bx_cpu. _16bit_base_reg[index];\
  }

#define BX_READ_16BIT_INDEX_REG(var, index) {\
  var = *bx_cpu. _16bit_index_reg[index];\
  }

#define BX_WRITE_8BIT_REG(index, val) {\
  if ((index) < 4) \
    bx_cpu. gen_reg[index].word.byte.rl = val; \
  else \
    bx_cpu. gen_reg[(index)-4].word.byte.rh = val; \
  }
#define BX_WRITE_16BIT_REG(index, val) {\
  bx_cpu. gen_reg[index].word.rx = val; \
  }
#define BX_WRITE_32BIT_REG(index, val) {\
  bx_cpu. gen_reg[index].erx = val; \
  }




#define TF bx_cpu. eflags.tf
#define IF bx_cpu. eflags.if_
#define DF bx_cpu. eflags.df

#define IOPL bx_cpu. eflags.iopl
#ifndef CPL
#define CPL  (bx_cpu. sregs[BX_SEG_REG_CS].selector.rpl)
#endif


#endif  // defined(NEED_CPU_REG_SHORTCUTS)

#define BX_DE_EXCEPTION   0 // Divide Error (fault)
#define BX_DB_EXCEPTION   1 // Debug (fault/trap)
#define BX_BP_EXCEPTION   3 // Breakpoint (trap)
#define BX_OF_EXCEPTION   4 // Overflow (trap)
#define BX_BR_EXCEPTION   5 // BOUND (fault)
#define BX_UD_EXCEPTION   6
#define BX_NM_EXCEPTION   7
#define BX_DF_EXCEPTION   8
#define BX_TS_EXCEPTION  10
#define BX_NP_EXCEPTION  11
#define BX_SS_EXCEPTION  12
#define BX_GP_EXCEPTION  13
#define BX_PF_EXCEPTION  14
#define BX_MF_EXCEPTION  16
#define BX_AC_EXCEPTION  17

/* MSR registers */
#define BX_MSR_P5_MC_ADDR	0x0000
#define BX_MSR_MC_TYPE		0x0001
#define BX_MSR_TSC		0x0010
#define BX_MSR_CESR		0x0011
#define BX_MSR_CTR0		0x0012
#define BX_MSR_CTR1		0x0013
#define BX_MSR_APICBASE		0x001b
#define BX_MSR_EBL_CR_POWERON	0x002a
#define BX_MSR_TEST_CTL		0x0033
#define BX_MSR_BIOS_UPDT_TRIG	0x0079
#define BX_MSR_BBL_CR_D0	0x0088
#define BX_MSR_BBL_CR_D1	0x0089
#define BX_MSR_BBL_CR_D2	0x008a
#define BX_MSR_BBL_CR_D3	0x008b	/* = BIOS_SIGN */
#define BX_MSR_PERFCTR0		0x00c1
#define BX_MSR_PERFCTR1		0x00c2
#define BX_MSR_MTRRCAP		0x00fe
#define BX_MSR_BBL_CR_ADDR	0x0116
#define BX_MSR_BBL_DECC		0x0118
#define BX_MSR_BBL_CR_CTL	0x0119
#define BX_MSR_BBL_CR_TRIG	0x011a
#define BX_MSR_BBL_CR_BUSY	0x011b
#define BX_MSR_BBL_CR_CTL3	0x011e
#define BX_MSR_MCG_CAP		0x0179
#define BX_MSR_MCG_STATUS	0x017a
#define BX_MSR_MCG_CTL		0x017b
#define BX_MSR_EVNTSEL0		0x0186
#define BX_MSR_EVNTSEL1		0x0187
#define BX_MSR_DEBUGCTLMSR	0x01d9
#define BX_MSR_LASTBRANCHFROMIP	0x01db
#define BX_MSR_LASTBRANCHTOIP	0x01dc
#define BX_MSR_LASTINTOIP	0x01dd
#define BX_MSR_ROB_CR_BKUPTMPDR6	0x01e0
#define BX_MSR_MTRRPHYSBASE0	0x0200
#define BX_MSR_MTRRPHYSMASK0	0x0201
#define BX_MSR_MTRRPHYSBASE1	0x0202

typedef struct {
  /* 31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16
   * ==|==|=====|==|==|==|==|==|==|==|==|==|==|==|==
   *  0| 0| 0| 0| 0| 0| 0| 0| 0| 0|ID|VP|VF|AC|VM|RF
   *
   * 15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0
   * ==|==|=====|==|==|==|==|==|==|==|==|==|==|==|==
   *  0|NT| IOPL|OF|DF|IF|TF|SF|ZF| 0|AF| 0|PF| 1|CF
   */

  // In order to get access to these fields from the Dynamic Translation
  // code, using only 8bit offsets, I needed to move these fields
  // together.
  Bit32u  cf;
  Bit32u  af;
  Bit32u  zf;
  Bit32u  sf;
  Bit32u  of;

  Boolean bit1;
  Bit8u   pf_byte;  /* PF derived from last result byte when needed */
  Boolean bit3;
  Boolean bit5;
  Boolean tf;
  Boolean if_;
  Boolean df;
#if BX_CPU_LEVEL >= 2
  Bit8u   iopl;
  Boolean nt;
#endif
  Boolean bit15;
#if BX_CPU_LEVEL >= 3
  Boolean rf;
  Boolean vm;
#endif
#if BX_CPU_LEVEL >= 4
  Boolean ac;  // alignment check
  // Boolean vif; // Virtual Interrupt Flag
  // Boolean vip; // Virtual Interrupt Pending
  Boolean id;  // late model 486 and beyond had CPUID
#endif
  } bx_flags_reg_t;


#if BX_CPU_LEVEL >= 2
typedef struct {
  Bit32u  val32; // 32bit value of register

  // bitfields broken out for efficient access
#if BX_CPU_LEVEL >= 3
  Boolean pg; // paging
#endif

// CR0 notes:
//   Each x86 level has its own quirks regarding how it handles
//   reserved bits.  I used DOS DEBUG.EXE in real mode on the
//   following processors, tried to clear bits 1..30, then tried
//   to set bits 1..30, to see how these bits are handled.
//   I found the following:
//
//   Processor    try to clear bits 1..30    try to set bits 1..30
//   386          7FFFFFF0                   7FFFFFFE
//   486DX2       00000010                   6005003E
//   Pentium      00000010                   7FFFFFFE
//   Pentium-II   00000010                   6005003E
//
// My assumptions:
//   All processors: bit 4 is hardwired to 1 (not true on all clones)
//   386: bits 5..30 of CR0 are also hardwired to 1
//   Pentium: reserved bits retain value set using mov cr0, reg32
//   486DX2/Pentium-II: reserved bits are hardwired to 0

#if BX_CPU_LEVEL >= 4
  Boolean cd; // cache disable
  Boolean nw; // no write-through
  Boolean am; // alignment mask
  Boolean wp; // write-protect
  Boolean ne; // numerics exception
#endif

  Boolean ts; // task switched
  Boolean em; // emulate math coprocessor
  Boolean mp; // monitor coprocessor
  Boolean pe; // protected mode enable
  } bx_cr0_t;
#endif

#if BX_CPU_LEVEL >= 5
typedef struct {
  Bit8u p5_mc_addr;
  Bit8u p5_mc_type;
  Bit8u tsc;
  Bit8u cesr;
  Bit8u ctr0;
  Bit8u ctr1;
  Bit64u apicbase;
  /* TODO finish of the others */
  } bx_regs_msr_t;
#endif

typedef struct { /* bx_selector_t */
  Bit16u value;   /* the 16bit value of the selector */
#if BX_CPU_LEVEL >= 2
    /* the following fields are extracted from the value field in protected
       mode only.  They're used for sake of efficiency */
  Bit16u index;   /* 13bit index extracted from value in protected mode */
  Bit8u  ti;      /* table indicator bit extracted from value */
  Bit8u  rpl;     /* RPL extracted from value */
#endif
  } bx_selector_t;



typedef struct {
  Boolean valid;         /* 0 = invalid, 1 = valid */
  Boolean p;             /* present */
  Bit8u   dpl;           /* descriptor privilege level 0..3 */
  Boolean segment;       /* 0 = system/gate, 1 = data/code segment */
  Bit8u   type;          /* For system & gate descriptors, only
                          *  0 = invalid descriptor (reserved)
                          *  1 = 286 available Task State Segment (TSS)
                          *  2 = LDT descriptor
                          *  3 = 286 busy Task State Segment (TSS)
                          *  4 = 286 call gate
                          *  5 = task gate
                          *  6 = 286 interrupt gate
                          *  7 = 286 trap gate
                          *  8 = (reserved)
                          *  9 = 386 available TSS
                          * 10 = (reserved)
                          * 11 = 386 busy TSS
                          * 12 = 386 call gate
                          * 13 = (reserved)
                          * 14 = 386 interrupt gate
                          * 15 = 386 trap gate */
  union {
  struct {
    Boolean executable;    /* 1=code, 0=data or stack segment */
    Boolean c_ed;          /* for code: 1=conforming,
                              for data/stack: 1=expand down */
    Boolean r_w;           /* for code: readable?, for data/stack: writeable? */
    Boolean a;             /* accessed? */
    Bit32u  base;          /* base address: 286=24bits, 386=32bits */
    Bit32u  limit;         /* limit: 286=16bits, 386=20bits */
    Bit32u  limit_scaled;  /* for efficiency, this contrived field is set to
                            * limit for byte granular, and
                            * (limit << 12) | 0xfff for page granular seg's
                            */
#if BX_CPU_LEVEL >= 3
    Boolean g;             /* granularity: 0=byte, 1=4K (page) */
    Boolean d_b;           /* default size: 0=16bit, 1=32bit */
    Boolean avl;           /* available for use by system */
#endif
    } segment;
  struct {
    Bit8u   word_count;    /* 5bits (0..31) #words to copy from caller's stack
                            * to called procedure's stack.  (call gates only)*/
    Bit16u  dest_selector;
    Bit16u  dest_offset;
    } gate286;
  struct {                 // type 5: Task Gate Descriptor
    Bit16u  tss_selector;  // TSS segment selector
    } taskgate;
#if BX_CPU_LEVEL >= 3
  struct {
    Bit8u   dword_count;   /* 5bits (0..31) #dwords to copy from caller's stack
                            * to called procedure's stack.  (call gates only)*/
    Bit16u  dest_selector;
    Bit32u  dest_offset;
    } gate386;
#endif
  struct {
    Bit32u  base;          /* 24 bit 286 TSS base  */
    Bit16u  limit;         /* 16 bit 286 TSS limit */
    } tss286;
#if BX_CPU_LEVEL >= 3
  struct {
    Bit32u  base;          /* 32 bit 386 TSS base  */
    Bit32u  limit;         /* 20 bit 386 TSS limit */
    Bit32u  limit_scaled;  // Same notes as for 'segment' field
    Boolean g;             /* granularity: 0=byte, 1=4K (page) */
    Boolean avl;           /* available for use by system */
    } tss386;
#endif
  struct {
    Bit32u  base;  /* 286=24 386+ =32 bit LDT base */
    Bit16u  limit; /* 286+ =16 bit LDT limit */
    } ldt;
    } u;

  } bx_descriptor_t;

typedef struct {
  bx_selector_t          selector;
  bx_descriptor_t  cache;
  } bx_segment_reg_t;

typedef void * (*BxVoidFPtr_t)(void);
class bx_cpu_c;

typedef struct BxInstruction_tag {
  // prefix stuff here...
  unsigned attr; // attribute from fetchdecode
  unsigned b1; // opcode1 byte
  unsigned rep_used;
  unsigned modrm; // mod-nnn-r/m byte
    unsigned mod;
    unsigned nnn;
    unsigned rm;
  Bit16u displ16u; // for 16-bit modrm forms
  Bit32u displ32u; // for 32-bit modrm forms
  unsigned seg;
  unsigned sib; // scale-index-base (2nd modrm byte)
    unsigned scale;
    unsigned index;
    unsigned base;
  Bit32u   addr_displacement; // address displacement
  Bit32u   rm_addr;
  Bit32u   Id;
  Bit16u   Iw;
  Bit8u    Ib;
  Bit8u    Ib2; // for ENTER_IwIb
  Bit16u   Iw2; // for JMP_Ap
  unsigned ilen; // instruction length
  unsigned os_32, as_32; // OperandSize/AddressSize is 32bit
  unsigned flags_in, flags_out; // flags needed, flags modified

#if BX_USE_CPU_SMF
  void (*ResolveModrm)(BxInstruction_tag *);
  void (*execute)(BxInstruction_tag *);
#else
  void (bx_cpu_c::*ResolveModrm)(BxInstruction_tag *);
  void (bx_cpu_c::*execute)(BxInstruction_tag *);
#endif

#if BX_DYNAMIC_TRANSLATION
  BxVoidFPtr_t DTResolveModrm;
#endif
#if BX_DYNAMIC_TRANSLATION
  unsigned DTAttr;
  Bit8u *   (*DTFPtr)(Bit8u *, BxInstruction_tag *);
  unsigned DTMemRegsUsed;
#endif
  } BxInstruction_t;

#if BX_USE_CPU_SMF
typedef void (*BxExecutePtr_t)(BxInstruction_t *);
#else
typedef void (bx_cpu_c::*BxExecutePtr_t)(BxInstruction_t *);
#endif


#if BX_DYNAMIC_TRANSLATION
typedef Bit8u * (*BxDTASResolveModrm_t)(Bit8u *, BxInstruction_t *,
  unsigned, unsigned);
#endif


#if BX_DYNAMIC_TRANSLATION
// Arrays of function pointers which handle a specific
// mod-rm address format
extern BxDTASResolveModrm_t  BxDTResolve32Mod0[];
extern BxDTASResolveModrm_t  BxDTResolve32Mod1or2[];
extern BxDTASResolveModrm_t  BxDTResolve32Mod0Base[];
extern BxDTASResolveModrm_t  BxDTResolve32Mod1or2Base[];
extern BxDTASResolveModrm_t  BxDTResolve16Mod1or2[];
extern BxDTASResolveModrm_t  BxDTResolve16Mod0[];
#endif


#if BX_CPU_LEVEL < 2
  /* no GDTR or IDTR register in an 8086 */
#else
typedef struct {
  Bit32u                 base;      /* base address: 24bits=286,32bits=386 */
  Bit16u                 limit;     /* limit, 16bits */
  } bx_global_segment_reg_t;
#endif




#if BX_USE_TLB
  typedef struct {
    Bit32u lpf; // linear page frame
    Bit32u ppf; // physical page frame
    Bit32u pte_addr; // Page Table Address for updating A & D bits
    Bit32u combined_access;
    } bx_TLB_entry;
#endif  // #if BX_USE_TLB

typedef struct {
  union {
    Bit32u erx;
    struct {
      union {
        Bit16u rx;
        struct {
          Bit8u rl;
          Bit8u rh;
          } byte;
        };
      Bit16u word_filler;
      } word;
    };
  } bx_gen_reg_t;

typedef enum {
  APIC_TYPE_NONE,
  APIC_TYPE_IOAPIC,
  APIC_TYPE_LOCAL_APIC
} bx_apic_type_t;

#define APIC_BASE_ADDR	0xfee00000	// default APIC address

// static member functions.  With SMF, there is only one CPU by definition.
typedef void (*BxDTShim_t)(void);

class BX_MEM_C;

class bx_cpu_c { //: public logfunctions {

public: // for now...

  char name[64];

  // General register set
  // eax: accumulator
  // ebx: base
  // ecx: count
  // edx: data
  // ebp: base pointer
  // esi: source index
  // edi: destination index
  // esp: stack pointer
  bx_gen_reg_t  gen_reg[8];

  Bit32u eip;    // instruction pointer
#if BX_CPU_LEVEL > 0
  // so that we can back up when handling faults, exceptions, etc.
  // we need to store the value of the instruction pointer, before
  // each fetch/execute cycle.
  Bit32u prev_eip;
#endif
  // A few pointer to functions for use by the dynamic translation
  // code.  Keep them close to the gen_reg declaration, so I can
  // use an 8bit offset to access them.

#if BX_DYNAMIC_TRANSLATION
  BxDTShim_t DTWrite8vShim;
  BxDTShim_t DTWrite16vShim;
  BxDTShim_t DTWrite32vShim;
  BxDTShim_t DTRead8vShim;
  BxDTShim_t DTRead16vShim;
  BxDTShim_t DTRead32vShim;
  BxDTShim_t DTReadRMW8vShim;
  BxDTShim_t DTReadRMW16vShim;
  BxDTShim_t DTReadRMW32vShim;
  BxDTShim_t DTWriteRMW8vShim;
  BxDTShim_t DTWriteRMW16vShim;
  BxDTShim_t DTWriteRMW32vShim;
  BxDTShim_t DTSetFlagsOSZAPCPtr;
  BxDTShim_t DTIndBrHandler;
  BxDTShim_t DTDirBrHandler;
#endif

  // status and control flags register set
  Bit32u   lf_flags_status;
  Boolean  lf_pf;
  bx_flags_reg_t eflags;

  bx_lf_flags_entry oszapc;
  bx_lf_flags_entry oszap;

  Bit32u prev_esp;

#define BX_INHIBIT_INTERRUPTS 0x01
#define BX_INHIBIT_DEBUG      0x02
  // What events to inhibit at any given time.  Certain instructions
  // inhibit interrupts, some debug exceptions and single-step traps.
  unsigned inhibit_mask;

  /* user segment register set */
  bx_segment_reg_t  sregs[6];

  /* system segment registers */
#if BX_CPU_LEVEL >= 2
  bx_global_segment_reg_t gdtr; /* global descriptor table register */
  bx_global_segment_reg_t idtr; /* interrupt descriptor table register */
#endif
  bx_segment_reg_t        ldtr; /* interrupt descriptor table register */
  bx_segment_reg_t        tr;   /* task register */


  /* debug registers 0-7 (unimplemented) */
#if BX_CPU_LEVEL >= 3
  Bit32u dr0;
  Bit32u dr1;
  Bit32u dr2;
  Bit32u dr3;
  Bit32u dr6;
  Bit32u dr7;
#endif

  /* TR3 - TR7 (Test Register 3-7), unimplemented */

  /* Control registers */
#if BX_CPU_LEVEL >= 2
  bx_cr0_t  cr0;
  Bit32u    cr1;
  Bit32u    cr2;
  Bit32u    cr3;
#endif
#if BX_CPU_LEVEL >= 4
  Bit32u    cr4;
#endif

#if BX_CPU_LEVEL >= 5
  bx_regs_msr_t	msr;  
#endif

  // pointer to the address space that this processor uses.
  BX_MEM_C *mem;

  Boolean EXT; /* 1 if processing external interrupt or exception
                * or if not related to current instruction,
                * 0 if current CS:IP caused exception */
  unsigned errorno;   /* signal exception during instruction emulation */

  Bit32u   debug_trap; // holds DR6 value to be set as well
  volatile Boolean async_event;
  volatile Boolean INTR;

  /* wether this CPU is the BSP always set for UP */
  Boolean bsp;
  // for accessing registers by index number
  Bit16u *_16bit_base_reg[8];
  Bit16u *_16bit_index_reg[8];
  Bit32u empty_register;

  // for decoding instructions; accessing seg reg's by index
  unsigned sreg_mod00_rm16[8];
  unsigned sreg_mod01_rm16[8];
  unsigned sreg_mod10_rm16[8];
  unsigned sreg_mod01_rm32[8];
  unsigned sreg_mod10_rm32[8];
  unsigned sreg_mod0_base32[8];
  unsigned sreg_mod1or2_base32[8];

  // for exceptions
  jmp_buf jmp_buf_env;
  Bit8u curr_exception[2];

  static const Boolean is_exception_OK[3][3];

  bx_segment_reg_t save_cs;
  bx_segment_reg_t save_ss;
  Bit32u           save_eip;
  Bit32u           save_esp;

  // For prefetch'ing instructions
  Bit32u bytesleft;
  Bit8u *fetch_ptr;
  Bit32u prev_linear_page;
  Bit32u prev_phy_page;
  Bit32u max_phy_addr;

#if BX_DEBUGGER
  Bit8u break_point;
#ifdef MAGIC_BREAKPOINT
  Bit8u magic_break;
#endif
  Bit8u stop_reason;
  Bit8u trace;
  Bit8u trace_reg;
  Bit8u mode_break;		/* BW */
  Boolean debug_vm;		/* BW contains current mode*/
  Bit8u show_eip;		/* BW record eip at special instr f.ex eip */
  Bit8u show_flag;		/* BW shows instr class executed */
  bx_guard_found_t guard_found;
#endif

  // for paging
#if BX_USE_TLB
  struct {
    bx_TLB_entry entry[BX_TLB_SIZE];
    } TLB;
#endif

  struct {
    Bit32u  paddress1;  // physical address after translation of 1st len1 bytes of data
    Bit32u  paddress2;  // physical address after translation of 2nd len2 bytes of data
    Bit32u  len1;       // number of bytes in page 1
    Bit32u  len2;       // number of bytes in page 2
    unsigned pages;     // number of pages access spans (1 or 2)
    } address_xlation;

  // for lazy flags processing
  static Boolean get_OF(void);
  static Boolean get_SF(void);
  static Boolean get_ZF(void);
  static Boolean get_AF(void);
  static Boolean get_PF(void);
  static Boolean get_CF(void);

  // constructors & destructors...
  bx_cpu_c();
  ~bx_cpu_c(void);
  void init (BX_MEM_C *addrspace);

  // prototypes for CPU instructions...
  static void ADD_EbGb(BxInstruction_t *);
  static void ADD_EdGd(BxInstruction_t *);
  static void ADD_GbEb(BxInstruction_t *);
  static void ADD_GdEd(BxInstruction_t *);
  static void ADD_ALIb(BxInstruction_t *);
  static void ADD_EAXId(BxInstruction_t *);
  static void OR_EbGb(BxInstruction_t *);
  static void OR_EdGd(BxInstruction_t *);
  static void OR_EwGw(BxInstruction_t *);
  static void OR_GbEb(BxInstruction_t *);
  static void OR_GdEd(BxInstruction_t *);
  static void OR_GwEw(BxInstruction_t *);
  static void OR_ALIb(BxInstruction_t *);
  static void OR_EAXId(BxInstruction_t *);
  static void OR_AXIw(BxInstruction_t *);

  static void PUSH_CS(BxInstruction_t *);
  static void PUSH_DS(BxInstruction_t *);
  static void POP_DS(BxInstruction_t *);
  static void PUSH_ES(BxInstruction_t *);
  static void POP_ES(BxInstruction_t *);
  static void PUSH_FS(BxInstruction_t *);
  static void POP_FS(BxInstruction_t *);
  static void PUSH_GS(BxInstruction_t *);
  static void POP_GS(BxInstruction_t *);
  static void PUSH_SS(BxInstruction_t *);
  static void POP_SS(BxInstruction_t *);

  static void ADC_EbGb(BxInstruction_t *);
  static void ADC_EdGd(BxInstruction_t *);
  static void ADC_GbEb(BxInstruction_t *);
  static void ADC_GdEd(BxInstruction_t *);
  static void ADC_ALIb(BxInstruction_t *);
  static void ADC_EAXId(BxInstruction_t *);
  static void SBB_EbGb(BxInstruction_t *);
  static void SBB_EdGd(BxInstruction_t *);
  static void SBB_GbEb(BxInstruction_t *);
  static void SBB_GdEd(BxInstruction_t *);
  static void SBB_ALIb(BxInstruction_t *);
  static void SBB_EAXId(BxInstruction_t *);

  static void AND_EbGb(BxInstruction_t *);
  static void AND_EdGd(BxInstruction_t *);
  static void AND_EwGw(BxInstruction_t *);
  static void AND_GbEb(BxInstruction_t *);
  static void AND_GdEd(BxInstruction_t *);
  static void AND_GwEw(BxInstruction_t *);
  static void AND_ALIb(BxInstruction_t *);
  static void AND_EAXId(BxInstruction_t *);
  static void AND_AXIw(BxInstruction_t *);
  static void DAA(BxInstruction_t *);
  static void SUB_EbGb(BxInstruction_t *);
  static void SUB_EdGd(BxInstruction_t *);
  static void SUB_GbEb(BxInstruction_t *);
  static void SUB_GdEd(BxInstruction_t *);
  static void SUB_ALIb(BxInstruction_t *);
  static void SUB_EAXId(BxInstruction_t *);
  static void DAS(BxInstruction_t *);

  static void XOR_EbGb(BxInstruction_t *);
  static void XOR_EdGd(BxInstruction_t *);
  static void XOR_EwGw(BxInstruction_t *);
  static void XOR_GbEb(BxInstruction_t *);
  static void XOR_GdEd(BxInstruction_t *);
  static void XOR_GwEw(BxInstruction_t *);
  static void XOR_ALIb(BxInstruction_t *);
  static void XOR_EAXId(BxInstruction_t *);
  static void XOR_AXIw(BxInstruction_t *);
  static void AAA(BxInstruction_t *);
  static void CMP_EbGb(BxInstruction_t *);
  static void CMP_EdGd(BxInstruction_t *);
  static void CMP_GbEb(BxInstruction_t *);
  static void CMP_GdEd(BxInstruction_t *);
  static void CMP_ALIb(BxInstruction_t *);
  static void CMP_EAXId(BxInstruction_t *);
  static void AAS(BxInstruction_t *);

  static void PUSHAD32(BxInstruction_t *);
  static void PUSHAD16(BxInstruction_t *);
  static void POPAD32(BxInstruction_t *);
  static void POPAD16(BxInstruction_t *);
  static void BOUND_GvMa(BxInstruction_t *);
  static void ARPL_EwGw(BxInstruction_t *);
  static void PUSH_Id(BxInstruction_t *);
  static void PUSH_Iw(BxInstruction_t *);
  static void IMUL_GdEdId(BxInstruction_t *);
  static void INSB_YbDX(BxInstruction_t *);
  static void INSW_YvDX(BxInstruction_t *);
  static void OUTSB_DXXb(BxInstruction_t *);
  static void OUTSW_DXXv(BxInstruction_t *);

  static void TEST_EbGb(BxInstruction_t *);
  static void TEST_EdGd(BxInstruction_t *);
  static void TEST_EwGw(BxInstruction_t *);
  static void XCHG_EbGb(BxInstruction_t *);
  static void XCHG_EdGd(BxInstruction_t *);
  static void XCHG_EwGw(BxInstruction_t *);
  static void MOV_EbGb(BxInstruction_t *);
  static void MOV_EdGd(BxInstruction_t *);
  static void MOV_EwGw(BxInstruction_t *);
  static void MOV_GbEb(BxInstruction_t *);
  static void MOV_GdEd(BxInstruction_t *);
  static void MOV_GwEw(BxInstruction_t *);
  static void MOV_EwSw(BxInstruction_t *);
  static void LEA_GdM(BxInstruction_t *);
  static void LEA_GwM(BxInstruction_t *);
  static void MOV_SwEw(BxInstruction_t *);
  static void POP_Ev(BxInstruction_t *);

  static void CBW(BxInstruction_t *);
  static void CWD(BxInstruction_t *);
  static void CALL32_Ap(BxInstruction_t *);
  static void CALL16_Ap(BxInstruction_t *);
  static void FWAIT(BxInstruction_t *);
  static void PUSHF_Fv(BxInstruction_t *);
  static void POPF_Fv(BxInstruction_t *);
  static void SAHF(BxInstruction_t *);
  static void LAHF(BxInstruction_t *);

  static void MOV_ALOb(BxInstruction_t *);
  static void MOV_EAXOd(BxInstruction_t *);
  static void MOV_AXOw(BxInstruction_t *);
  static void MOV_ObAL(BxInstruction_t *);
  static void MOV_OdEAX(BxInstruction_t *);
  static void MOV_OwAX(BxInstruction_t *);
  static void MOVSB_XbYb(BxInstruction_t *);
  static void MOVSW_XvYv(BxInstruction_t *);
  static void CMPSB_XbYb(BxInstruction_t *);
  static void CMPSW_XvYv(BxInstruction_t *);
  static void TEST_ALIb(BxInstruction_t *);
  static void TEST_EAXId(BxInstruction_t *);
  static void TEST_AXIw(BxInstruction_t *);
  static void STOSB_YbAL(BxInstruction_t *);
  static void STOSW_YveAX(BxInstruction_t *);
  static void LODSB_ALXb(BxInstruction_t *);
  static void LODSW_eAXXv(BxInstruction_t *);
  static void SCASB_ALXb(BxInstruction_t *);
  static void SCASW_eAXXv(BxInstruction_t *);

  static void RETnear32(BxInstruction_t *);
  static void RETnear16(BxInstruction_t *);
  static void LES_GvMp(BxInstruction_t *);
  static void LDS_GvMp(BxInstruction_t *);
  static void MOV_EbIb(BxInstruction_t *);
  static void MOV_EdId(BxInstruction_t *);
  static void MOV_EwIw(BxInstruction_t *);
  static void ENTER_IwIb(BxInstruction_t *);
  static void LEAVE(BxInstruction_t *);
  static void RETfar32(BxInstruction_t *);
  static void RETfar16(BxInstruction_t *);

  static void INT1(BxInstruction_t *);
  static void INT3(BxInstruction_t *);
  static void INT_Ib(BxInstruction_t *);
  static void INTO(BxInstruction_t *);
  static void IRET32(BxInstruction_t *);
  static void IRET16(BxInstruction_t *);

  static void AAM(BxInstruction_t *);
  static void AAD(BxInstruction_t *);
  static void SALC(BxInstruction_t *);
  static void XLAT(BxInstruction_t *);

  static void LOOPNE_Jb(BxInstruction_t *);
  static void LOOPE_Jb(BxInstruction_t *);
  static void LOOP_Jb(BxInstruction_t *);
  static void JCXZ_Jb(BxInstruction_t *);
  static void IN_ALIb(BxInstruction_t *);
  static void IN_eAXIb(BxInstruction_t *);
  static void OUT_IbAL(BxInstruction_t *);
  static void OUT_IbeAX(BxInstruction_t *);
  static void CALL_Aw(BxInstruction_t *);
  static void CALL_Ad(BxInstruction_t *);
  static void JMP_Jd(BxInstruction_t *);
  static void JMP_Jw(BxInstruction_t *);
  static void JMP_Ap(BxInstruction_t *);
  static void IN_ALDX(BxInstruction_t *);
  static void IN_eAXDX(BxInstruction_t *);
  static void OUT_DXAL(BxInstruction_t *);
  static void OUT_DXeAX(BxInstruction_t *);

  static void HLT(BxInstruction_t *);
  static void CMC(BxInstruction_t *);
  static void CLC(BxInstruction_t *);
  static void STC(BxInstruction_t *);
  static void CLI(BxInstruction_t *);
  static void STI(BxInstruction_t *);
  static void CLD(BxInstruction_t *);
  static void STD(BxInstruction_t *);


  static void LAR_GvEw(BxInstruction_t *);
  static void LSL_GvEw(BxInstruction_t *);
  static void CLTS(BxInstruction_t *);
  static void INVD(BxInstruction_t *);
  static void WBINVD(BxInstruction_t *);

  static void MOV_CdRd(BxInstruction_t *);
  static void MOV_DdRd(BxInstruction_t *);
  static void MOV_RdCd(BxInstruction_t *);
  static void MOV_RdDd(BxInstruction_t *);
  static void MOV_TdRd(BxInstruction_t *);
  static void MOV_RdTd(BxInstruction_t *);

  static void JCC_Jd(BxInstruction_t *);
  static void JCC_Jw(BxInstruction_t *);

  static void SETO_Eb(BxInstruction_t *);
  static void SETNO_Eb(BxInstruction_t *);
  static void SETB_Eb(BxInstruction_t *);
  static void SETNB_Eb(BxInstruction_t *);
  static void SETZ_Eb(BxInstruction_t *);
  static void SETNZ_Eb(BxInstruction_t *);
  static void SETBE_Eb(BxInstruction_t *);
  static void SETNBE_Eb(BxInstruction_t *);
  static void SETS_Eb(BxInstruction_t *);
  static void SETNS_Eb(BxInstruction_t *);
  static void SETP_Eb(BxInstruction_t *);
  static void SETNP_Eb(BxInstruction_t *);
  static void SETL_Eb(BxInstruction_t *);
  static void SETNL_Eb(BxInstruction_t *);
  static void SETLE_Eb(BxInstruction_t *);
  static void SETNLE_Eb(BxInstruction_t *);

  static void CPUID(BxInstruction_t *);
  static void BT_EvGv(BxInstruction_t *);
  static void SHLD_EdGd(BxInstruction_t *);
  static void SHLD_EwGw(BxInstruction_t *);


  static void BTS_EvGv(BxInstruction_t *);

  static void SHRD_EwGw(BxInstruction_t *);
  static void SHRD_EdGd(BxInstruction_t *);

  static void IMUL_GdEd(BxInstruction_t *);

  static void LSS_GvMp(BxInstruction_t *);
  static void BTR_EvGv(BxInstruction_t *);
  static void LFS_GvMp(BxInstruction_t *);
  static void LGS_GvMp(BxInstruction_t *);
  static void MOVZX_GdEb(BxInstruction_t *);
  static void MOVZX_GwEb(BxInstruction_t *);
  static void MOVZX_GdEw(BxInstruction_t *);
  static void MOVZX_GwEw(BxInstruction_t *);
  static void BTC_EvGv(BxInstruction_t *);
  static void BSF_GvEv(BxInstruction_t *);
  static void BSR_GvEv(BxInstruction_t *);
  static void MOVSX_GdEb(BxInstruction_t *);
  static void MOVSX_GwEb(BxInstruction_t *);
  static void MOVSX_GdEw(BxInstruction_t *);
  static void MOVSX_GwEw(BxInstruction_t *);

  static void BSWAP_EAX(BxInstruction_t *);
  static void BSWAP_ECX(BxInstruction_t *);
  static void BSWAP_EDX(BxInstruction_t *);
  static void BSWAP_EBX(BxInstruction_t *);
  static void BSWAP_ESP(BxInstruction_t *);
  static void BSWAP_EBP(BxInstruction_t *);
  static void BSWAP_ESI(BxInstruction_t *);
  static void BSWAP_EDI(BxInstruction_t *);

  static void ADD_EbIb(BxInstruction_t *);
  static void ADC_EbIb(BxInstruction_t *);
  static void SBB_EbIb(BxInstruction_t *);
  static void SUB_EbIb(BxInstruction_t *);
  static void CMP_EbIb(BxInstruction_t *);

  static void XOR_EbIb(BxInstruction_t *);
  static void OR_EbIb(BxInstruction_t *);
  static void AND_EbIb(BxInstruction_t *);

  static void ADD_EdId(BxInstruction_t *);
  static void OR_EdId(BxInstruction_t *);
  static void OR_EwIw(BxInstruction_t *);
  static void ADC_EdId(BxInstruction_t *);
  static void SBB_EdId(BxInstruction_t *);
  static void AND_EdId(BxInstruction_t *);
  static void AND_EwIw(BxInstruction_t *);
  static void SUB_EdId(BxInstruction_t *);
  static void XOR_EdId(BxInstruction_t *);
  static void XOR_EwIw(BxInstruction_t *);
  static void CMP_EdId(BxInstruction_t *);

  static void ROL_Eb(BxInstruction_t *);
  static void ROR_Eb(BxInstruction_t *);
  static void RCL_Eb(BxInstruction_t *);
  static void RCR_Eb(BxInstruction_t *);
  static void SHL_Eb(BxInstruction_t *);
  static void SHR_Eb(BxInstruction_t *);
  static void SAR_Eb(BxInstruction_t *);

  static void ROL_Ed(BxInstruction_t *);
  static void ROL_Ew(BxInstruction_t *);
  static void ROR_Ed(BxInstruction_t *);
  static void ROR_Ew(BxInstruction_t *);
  static void RCL_Ed(BxInstruction_t *);
  static void RCL_Ew(BxInstruction_t *);
  static void RCR_Ed(BxInstruction_t *);
  static void RCR_Ew(BxInstruction_t *);
  static void SHL_Ed(BxInstruction_t *);
  static void SHL_Ew(BxInstruction_t *);
  static void SHR_Ed(BxInstruction_t *);
  static void SHR_Ew(BxInstruction_t *);
  static void SAR_Ed(BxInstruction_t *);
  static void SAR_Ew(BxInstruction_t *);

  static void TEST_EbIb(BxInstruction_t *);
  static void NOT_Eb(BxInstruction_t *);
  static void NEG_Eb(BxInstruction_t *);
  static void MUL_ALEb(BxInstruction_t *);
  static void IMUL_ALEb(BxInstruction_t *);
  static void DIV_ALEb(BxInstruction_t *);
  static void IDIV_ALEb(BxInstruction_t *);

  static void TEST_EdId(BxInstruction_t *);
  static void TEST_EwIw(BxInstruction_t *);
  static void NOT_Ed(BxInstruction_t *);
  static void NOT_Ew(BxInstruction_t *);
  static void NEG_Ed(BxInstruction_t *);
  static void MUL_EAXEd(BxInstruction_t *);
  static void IMUL_EAXEd(BxInstruction_t *);
  static void DIV_EAXEd(BxInstruction_t *);
  static void IDIV_EAXEd(BxInstruction_t *);

  static void INC_Eb(BxInstruction_t *);
  static void DEC_Eb(BxInstruction_t *);

  static void INC_Ed(BxInstruction_t *);
  static void DEC_Ed(BxInstruction_t *);
  static void CALL_Ed(BxInstruction_t *);
  static void CALL_Ew(BxInstruction_t *);
  static void CALL32_Ep(BxInstruction_t *);
  static void CALL16_Ep(BxInstruction_t *);
  static void JMP_Ed(BxInstruction_t *);
  static void JMP_Ew(BxInstruction_t *);
  static void JMP32_Ep(BxInstruction_t *);
  static void JMP16_Ep(BxInstruction_t *);
  static void PUSH_Ed(BxInstruction_t *);
  static void PUSH_Ew(BxInstruction_t *);

  static void SLDT_Ew(BxInstruction_t *);
  static void STR_Ew(BxInstruction_t *);
  static void LLDT_Ew(BxInstruction_t *);
  static void LTR_Ew(BxInstruction_t *);
  static void VERR_Ew(BxInstruction_t *);
  static void VERW_Ew(BxInstruction_t *);

  static void SGDT_Ms(BxInstruction_t *);
  static void SIDT_Ms(BxInstruction_t *);
  static void LGDT_Ms(BxInstruction_t *);
  static void LIDT_Ms(BxInstruction_t *);
  static void SMSW_Ew(BxInstruction_t *);
  static void LMSW_Ew(BxInstruction_t *);


  static void BT_EvIb(BxInstruction_t *);
  static void BTS_EvIb(BxInstruction_t *);
  static void BTR_EvIb(BxInstruction_t *);
  static void BTC_EvIb(BxInstruction_t *);

  static void ESC0(BxInstruction_t *);
  static void ESC1(BxInstruction_t *);
  static void ESC2(BxInstruction_t *);
  static void ESC3(BxInstruction_t *);
  static void ESC4(BxInstruction_t *);
  static void ESC5(BxInstruction_t *);
  static void ESC6(BxInstruction_t *);
  static void ESC7(BxInstruction_t *);

  static void fpu_execute(BxInstruction_t *i);
  static void fpu_init(void);
  static void fpu_print_regs (void);

  static void CMPXCHG_XBTS(BxInstruction_t *);
  static void CMPXCHG_IBTS(BxInstruction_t *);
  static void CMPXCHG_EbGb(BxInstruction_t *);
  static void CMPXCHG_EdGd(BxInstruction_t *);
  static void CMPXCHG8B(BxInstruction_t *);
  static void XADD_EbGb(BxInstruction_t *);
  static void XADD_EdGd(BxInstruction_t *);
  static void RETnear32_Iw(BxInstruction_t *);
  static void RETnear16_Iw(BxInstruction_t *);
  static void RETfar32_Iw(BxInstruction_t *);
  static void RETfar16_Iw(BxInstruction_t *);

  static void LOADALL(BxInstruction_t *);
  static void CMOV_GdEd(BxInstruction_t *);
  static void CMOV_GwEw(BxInstruction_t *);

  static void ADD_EwGw(BxInstruction_t *);
  static void ADD_GwEw(BxInstruction_t *);
  static void ADD_AXIw(BxInstruction_t *);
  static void ADC_EwGw(BxInstruction_t *);
  static void ADC_GwEw(BxInstruction_t *);
  static void ADC_AXIw(BxInstruction_t *);
  static void SBB_EwGw(BxInstruction_t *);
  static void SBB_GwEw(BxInstruction_t *);
  static void SBB_AXIw(BxInstruction_t *);
  static void SBB_EwIw(BxInstruction_t *);
  static void SUB_EwGw(BxInstruction_t *);
  static void SUB_GwEw(BxInstruction_t *);
  static void SUB_AXIw(BxInstruction_t *);
  static void CMP_EwGw(BxInstruction_t *);
  static void CMP_GwEw(BxInstruction_t *);
  static void CMP_AXIw(BxInstruction_t *);
  static void CWDE(BxInstruction_t *);
  static void CDQ(BxInstruction_t *);
  static void XADD_EwGw(BxInstruction_t *);
  static void ADD_EwIw(BxInstruction_t *);
  static void ADC_EwIw(BxInstruction_t *);
  static void SUB_EwIw(BxInstruction_t *);
  static void CMP_EwIw(BxInstruction_t *);
  static void NEG_Ew(BxInstruction_t *);
  static void INC_Ew(BxInstruction_t *);
  static void DEC_Ew(BxInstruction_t *);
  static void CMPXCHG_EwGw(BxInstruction_t *);
  static void MUL_AXEw(BxInstruction_t *);
  static void IMUL_AXEw(BxInstruction_t *);
  static void DIV_AXEw(BxInstruction_t *);
  static void IDIV_AXEw(BxInstruction_t *);
  static void IMUL_GwEwIw(BxInstruction_t *);
  static void IMUL_GwEw(BxInstruction_t *);
  static void NOP(BxInstruction_t *);
  static void MOV_RLIb(BxInstruction_t *);
  static void MOV_RHIb(BxInstruction_t *);
  static void MOV_RXIw(BxInstruction_t *);
  static void MOV_ERXId(BxInstruction_t *);
  static void INC_RX(BxInstruction_t *);
  static void DEC_RX(BxInstruction_t *);
  static void INC_ERX(BxInstruction_t *);
  static void DEC_ERX(BxInstruction_t *);
  static void PUSH_RX(BxInstruction_t *);
  static void POP_RX(BxInstruction_t *);
  static void PUSH_ERX(BxInstruction_t *);
  static void POP_ERX(BxInstruction_t *);
  static void POP_Ew(BxInstruction_t *);
  static void POP_Ed(BxInstruction_t *);
  static void XCHG_RXAX(BxInstruction_t *);
  static void XCHG_ERXEAX(BxInstruction_t *);

  // mch added
  static void INVLPG(BxInstruction_t *);
  static void wait_for_interrupt();
  static void RSM(BxInstruction_t *);

  static void WRMSR(BxInstruction_t *);
  static void RDTSC(BxInstruction_t *);
  static void RDMSR(BxInstruction_t *);
  static void SetCR0(Bit32u val_32);
  static void dynamic_translate(void);
  static void dynamic_init(void);
  static unsigned FetchDecode(Bit8u *, BxInstruction_t *, unsigned, Boolean);
  static void UndefinedOpcode(BxInstruction_t *);
  static void BxError(BxInstruction_t *i);
  static void BxResolveError(BxInstruction_t *i);

  static void Resolve16Mod0Rm0(BxInstruction_t *);
  static void Resolve16Mod0Rm1(BxInstruction_t *);
  static void Resolve16Mod0Rm2(BxInstruction_t *);
  static void Resolve16Mod0Rm3(BxInstruction_t *);
  static void Resolve16Mod0Rm4(BxInstruction_t *);
  static void Resolve16Mod0Rm5(BxInstruction_t *);
  static void Resolve16Mod0Rm7(BxInstruction_t *);

  static void Resolve16Mod1or2Rm0(BxInstruction_t *);
  static void Resolve16Mod1or2Rm1(BxInstruction_t *);
  static void Resolve16Mod1or2Rm2(BxInstruction_t *);
  static void Resolve16Mod1or2Rm3(BxInstruction_t *);
  static void Resolve16Mod1or2Rm4(BxInstruction_t *);
  static void Resolve16Mod1or2Rm5(BxInstruction_t *);
  static void Resolve16Mod1or2Rm6(BxInstruction_t *);
  static void Resolve16Mod1or2Rm7(BxInstruction_t *);

  static void Resolve32Mod0Rm0(BxInstruction_t *);
  static void Resolve32Mod0Rm1(BxInstruction_t *);
  static void Resolve32Mod0Rm2(BxInstruction_t *);
  static void Resolve32Mod0Rm3(BxInstruction_t *);
  static void Resolve32Mod0Rm6(BxInstruction_t *);
  static void Resolve32Mod0Rm7(BxInstruction_t *);

  static void Resolve32Mod1or2Rm0(BxInstruction_t *);
  static void Resolve32Mod1or2Rm1(BxInstruction_t *);
  static void Resolve32Mod1or2Rm2(BxInstruction_t *);
  static void Resolve32Mod1or2Rm3(BxInstruction_t *);
  static void Resolve32Mod1or2Rm5(BxInstruction_t *);
  static void Resolve32Mod1or2Rm6(BxInstruction_t *);
  static void Resolve32Mod1or2Rm7(BxInstruction_t *);

  static void Resolve32Mod0Base0(BxInstruction_t *);
  static void Resolve32Mod0Base1(BxInstruction_t *);
  static void Resolve32Mod0Base2(BxInstruction_t *);
  static void Resolve32Mod0Base3(BxInstruction_t *);
  static void Resolve32Mod0Base4(BxInstruction_t *);
  static void Resolve32Mod0Base5(BxInstruction_t *);
  static void Resolve32Mod0Base6(BxInstruction_t *);
  static void Resolve32Mod0Base7(BxInstruction_t *);

  static void Resolve32Mod1or2Base0(BxInstruction_t *);
  static void Resolve32Mod1or2Base1(BxInstruction_t *);
  static void Resolve32Mod1or2Base2(BxInstruction_t *);
  static void Resolve32Mod1or2Base3(BxInstruction_t *);
  static void Resolve32Mod1or2Base4(BxInstruction_t *);
  static void Resolve32Mod1or2Base5(BxInstruction_t *);
  static void Resolve32Mod1or2Base6(BxInstruction_t *);
  static void Resolve32Mod1or2Base7(BxInstruction_t *);


  static void REP(void (*)(void));
  static void REP_ZF(void (*)(void), unsigned rep_prefix);
#if BX_DEBUGGER
  static void     dbg_take_irq(void);
  static void     dbg_force_interrupt(unsigned vector);
  static void     dbg_take_dma(void);
  static Boolean  dbg_get_cpu(bx_dbg_cpu_t *cpu);
  static Boolean  dbg_set_cpu(bx_dbg_cpu_t *cpu);
  static Boolean  dbg_set_reg(unsigned reg, Bit32u val);
  static Bit32u   dbg_get_reg(unsigned reg);
  static Boolean  dbg_get_sreg(bx_dbg_sreg_t *sreg, unsigned sreg_no);
  static unsigned dbg_query_pending(void);
  static Bit32u   dbg_get_descriptor_l(bx_descriptor_t *);
  static Bit32u   dbg_get_descriptor_h(bx_descriptor_t *);
  static Bit32u   dbg_get_eflags(void);
  static Boolean  dbg_is_begin_instr_bpoint(Bit32u cs, Bit32u eip, Bit32u laddr,
                                            Bit32u is_32);
  static Boolean  dbg_is_end_instr_bpoint(Bit32u cs, Bit32u eip,
                                          Bit32u laddr, Bit32u is_32);
#endif
#if BX_DEBUGGER || BX_DISASM || BX_INSTRUMENTATION
  static void     dbg_xlate_linear2phy(Bit32u linear, Bit32u *phy, Boolean *valid);
#endif
  static void     atexit(void);

  // now for some ancillary functions...
  static void cpu_loop(Bit32s max_instr_count);
  static void decode_exgx16(unsigned need_fetch);
  static void decode_exgx32(unsigned need_fetch);

  static void prefetch(void);
  static void revalidate_prefetch_q(void);
  static void invalidate_prefetch_q(void);

  static void write_virtual_checks(bx_segment_reg_t *seg, Bit32u offset, unsigned length);
  static void read_virtual_checks(bx_segment_reg_t *seg, Bit32u offset, unsigned length);
  static void write_virtual_byte(unsigned seg, Bit32u offset, Bit8u *data);
  static void write_virtual_word(unsigned seg, Bit32u offset, Bit16u *data);
  static void write_virtual_dword(unsigned seg, Bit32u offset, Bit32u *data);
  static void read_virtual_byte(unsigned seg, Bit32u offset, Bit8u *data);
  static void read_virtual_word(unsigned seg, Bit32u offset, Bit16u *data);
  static void read_virtual_dword(unsigned seg, Bit32u offset, Bit32u *data);

  static void read_RMW_virtual_byte(unsigned seg, Bit32u offset, Bit8u *data);
  static void read_RMW_virtual_word(unsigned seg, Bit32u offset, Bit16u *data);
  static void read_RMW_virtual_dword(unsigned seg, Bit32u offset, Bit32u *data);
  static void write_RMW_virtual_byte(Bit8u val8);
  static void write_RMW_virtual_word(Bit16u val16);
  static void write_RMW_virtual_dword(Bit32u val32);

  static void access_linear(Bit32u address, unsigned length, unsigned pl,
                     unsigned rw, void *data);
  static Bit32u itranslate_linear(Bit32u laddress, unsigned pl);
  static Bit32u dtranslate_linear(Bit32u laddress, unsigned pl, unsigned rw);
  static void TLB_flush(void);
  static void TLB_clear(void);
  static void TLB_init(void);
  static void set_INTR(Boolean value);
  static char *strseg(bx_segment_reg_t *seg);
  static void interrupt(Bit8u vector, Boolean is_INT, Boolean is_error_code,
                 Bit16u error_code);
#if BX_CPU_LEVEL >= 2
  static void exception(unsigned vector, Bit16u error_code, Boolean is_INT);
#endif
  static int  int_number(bx_segment_reg_t *seg);
  static void shutdown_cpu(void);
  static void enable_paging(void);
  static void disable_paging(void);
  static void CR3_change(Bit32u value32);
  static void reset(unsigned source);

  static void jump_protected(BxInstruction_t *, Bit16u cs, Bit32u disp32);
  static void call_protected(BxInstruction_t *, Bit16u cs, Bit32u disp32);
  static void return_protected(BxInstruction_t *, Bit16u pop_bytes);
  static void iret_protected(BxInstruction_t *);
  static void validate_seg_regs(void);
  static void stack_return_to_v86(Bit32u new_eip, Bit32u raw_cs_selector,
                                     Bit32u flags32);
  static void stack_return_from_v86(BxInstruction_t *);
  static void init_v8086_mode(void);
  static void v8086_message(void);
  static void task_switch(bx_selector_t *selector,
                     bx_descriptor_t *descriptor,
                     unsigned source,
                     Bit32u dword1, Bit32u dword2);
  static void get_SS_ESP_from_TSS(unsigned pl, Bit16u *ss, Bit32u *esp);
  static void write_flags(Bit16u flags, Boolean change_IOPL, Boolean change_IF);
  static void write_eflags(Bit32u eflags, Boolean change_IOPL, Boolean change_IF,
                    Boolean change_VM, Boolean change_RF);
  static Bit16u read_flags(void);
  static Bit32u read_eflags(void);

  static Bit8u   inp8(Bit16u addr);
  static void    outp8(Bit16u addr, Bit8u value);
  static Bit16u  inp16(Bit16u addr);
  static void    outp16(Bit16u addr, Bit16u value);
  static Bit32u  inp32(Bit16u addr);
  static void    outp32(Bit16u addr, Bit32u value);
  static Boolean allow_io(Bit16u addr, unsigned len);
  static void    enter_protected_mode(void);
  static void    enter_real_mode(void);
  static void    parse_selector(Bit16u raw_selector, bx_selector_t *selector);
  static void    parse_descriptor(Bit32u dword1, Bit32u dword2, bx_descriptor_t *temp);
  static void    load_ldtr(bx_selector_t *selector, bx_descriptor_t *descriptor);
  static void    load_cs(bx_selector_t *selector, bx_descriptor_t *descriptor, Bit8u cpl);
  static void    load_ss(bx_selector_t *selector, bx_descriptor_t *descriptor, Bit8u cpl);
  static void    fetch_raw_descriptor(bx_selector_t *selector,
                               Bit32u *dword1, Bit32u *dword2, Bit8u exception);
  static void    load_seg_reg(bx_segment_reg_t *seg, Bit16u new_value);
  static Boolean fetch_raw_descriptor2(bx_selector_t *selector,
                                Bit32u *dword1, Bit32u *dword2);
  static void    push_16(Bit16u value16);
  static void    push_32(Bit32u value32);
  static void    pop_16(Bit16u *value16_ptr);
  static void    pop_32(Bit32u *value32_ptr);
  static Boolean can_push(bx_descriptor_t *descriptor, Bit32u esp, Bit32u bytes);
  static Boolean can_pop(Bit32u bytes);
  static void    sanity_checks(void);

  static void    debug(Bit32u offset);

#if BX_X86_DEBUGGER
  // x86 hardware debug support
  static Bit32u  hwdebug_compare(Bit32u laddr, unsigned size,
                                 unsigned opa, unsigned opb);
#endif

  static BX_CPP_INLINE void set_CF(Boolean val);
  static BX_CPP_INLINE void set_AF(Boolean val);
  static BX_CPP_INLINE void set_ZF(Boolean val);
  static BX_CPP_INLINE void set_SF(Boolean val);
  static BX_CPP_INLINE void set_OF(Boolean val);
  static BX_CPP_INLINE void set_PF(Boolean val);
  static BX_CPP_INLINE void set_PF_base(Bit8u val);


  static BX_CPP_INLINE void set_AX(Bit16u ax);
  static BX_CPP_INLINE void set_BX(Bit16u bx);
  static BX_CPP_INLINE void set_CX(Bit16u cx);
  static BX_CPP_INLINE void set_DX(Bit16u dx);
  static BX_CPP_INLINE void set_AL(Bit8u  al);
  static BX_CPP_INLINE void set_AH(Bit8u  ah);
  static BX_CPP_INLINE void set_BL(Bit8u  bl);
  static BX_CPP_INLINE void set_BH(Bit8u  bh);
  static BX_CPP_INLINE void set_CL(Bit8u  cl);
  static BX_CPP_INLINE void set_CH(Bit8u  ch);
  static BX_CPP_INLINE void set_DL(Bit8u  dl);
  static BX_CPP_INLINE void set_DH(Bit8u  dh);

  static BX_CPP_INLINE Bit8u get_AL(void);
  static BX_CPP_INLINE Bit8u get_AH(void);
  static BX_CPP_INLINE Bit8u get_BL(void);
  static BX_CPP_INLINE Bit8u get_BH(void);
  static BX_CPP_INLINE Bit8u get_CL(void);
  static BX_CPP_INLINE Bit8u get_CH(void);
  static BX_CPP_INLINE Bit8u get_DL(void);
  static BX_CPP_INLINE Bit8u get_DH(void);

  static BX_CPP_INLINE Bit16u get_AX(void);
  static BX_CPP_INLINE Bit16u get_BX(void);
  static BX_CPP_INLINE Bit16u get_CX(void);
  static BX_CPP_INLINE Bit16u get_DX(void);

#if BX_CPU_LEVEL >= 2
  static BX_CPP_INLINE Boolean real_mode(void);
#endif
#if BX_CPU_LEVEL >= 3
  static BX_CPP_INLINE Boolean protected_mode(void);
  static BX_CPP_INLINE Boolean v8086_mode(void);
#endif
#if BX_SUPPORT_APIC
  bx_local_apic_c local_apic;
  Boolean int_from_local_apic;
#endif
  };


#if BX_X86_DEBUGGER
#define BX_HWDebugInstruction   0x00
#define BX_HWDebugMemW          0x01
#define BX_HWDebugIO            0x02
#define BX_HWDebugMemRW         0x03
#endif


#if BX_SMP_PROCESSORS==1
// single processor simulation, so there's one of everything
extern bx_cpu_c       bx_cpu;
#else
// multiprocessor simulation, we need an array of cpus and memories
extern bx_cpu_c       *bx_cpu_array[BX_SMP_PROCESSORS];
#endif

#if defined(NEED_CPU_REG_SHORTCUTS)

static BX_CPP_INLINE void  set_AX(Bit16u ax) { AX = ax; };
static BX_CPP_INLINE void  set_BX(Bit16u bx) { BX = bx; };
static BX_CPP_INLINE void  set_CX(Bit16u cx) { CX = cx; };
static BX_CPP_INLINE void  set_DX(Bit16u dx) { DX = dx; };
static BX_CPP_INLINE void  set_AL(Bit8u  al) { AL = al; };
static BX_CPP_INLINE void  set_AH(Bit8u  ah) { AH = ah; };
static BX_CPP_INLINE void  set_BL(Bit8u  bl) { BL = bl; };
static BX_CPP_INLINE void  set_BH(Bit8u  bh) { BH = bh; };
static BX_CPP_INLINE void  set_CL(Bit8u  cl) { CL = cl; };
static BX_CPP_INLINE void  set_CH(Bit8u  ch) { CH = ch; };
static BX_CPP_INLINE void  set_DL(Bit8u  dl) { DL = dl; };
static BX_CPP_INLINE void  set_DH(Bit8u  dh) { DH = dh; };

static BX_CPP_INLINE Bit8u  get_AL(void) { return(AL); };
static BX_CPP_INLINE Bit8u  get_AH(void) { return(AH); };
static BX_CPP_INLINE Bit8u  get_BL(void) { return(BL); };
static BX_CPP_INLINE Bit8u  get_BH(void) { return(BH); };
static BX_CPP_INLINE Bit8u  get_CL(void) { return(CL); };
static BX_CPP_INLINE Bit8u  get_CH(void) { return(CH); };
static BX_CPP_INLINE Bit8u  get_DL(void) { return(DL); };
static BX_CPP_INLINE Bit8u  get_DH(void) { return(DH); };

static BX_CPP_INLINE Bit16u  get_AX(void) { return(AX); };
static BX_CPP_INLINE Bit16u  get_BX(void) { return(BX); };
static BX_CPP_INLINE Bit16u  get_CX(void) { return(CX); };
static BX_CPP_INLINE Bit16u  get_DX(void) { return(DX); };

#endif


#if BX_CPU_LEVEL >= 2
  BX_CPP_INLINE Boolean bx_cpu_c::real_mode(void) { return( !bx_cpu. cr0.pe ); };
#endif

#if BX_CPU_LEVEL == 2
  BX_CPP_INLINE Boolean bx_cpu_c::protected_mode(void) { return( bx_cpu. cr0.pe ); };
#endif


#if BX_CPU_LEVEL >= 3
#  if BX_SUPPORT_V8086_MODE
  BX_CPP_INLINE Boolean
bx_cpu_c::v8086_mode(void) {
  return(bx_cpu. eflags.vm);
  }

  BX_CPP_INLINE Boolean
bx_cpu_c::protected_mode(void) {
  return(bx_cpu. cr0.pe && !bx_cpu. eflags.vm);
  }
#  else
  BX_CPP_INLINE Boolean
bx_cpu_c::v8086_mode(void) {
  return(0);
  }

  BX_CPP_INLINE Boolean
bx_cpu_c::protected_mode(void) {
  return(bx_cpu. cr0.pe);
  }
#  endif
#endif

    BX_CPP_INLINE void
bx_cpu_c::set_CF(Boolean val) {
    bx_cpu. lf_flags_status &= 0xfffff0;
    bx_cpu. eflags.cf = val;
    }

    BX_CPP_INLINE void
bx_cpu_c::set_AF(Boolean val) {
    bx_cpu. lf_flags_status &= 0xfff0ff;
    bx_cpu. eflags.af = val;
    }

    BX_CPP_INLINE void
bx_cpu_c::set_ZF(Boolean val) {
    bx_cpu. lf_flags_status &= 0xff0fff;
    bx_cpu. eflags.zf = val;
    }

    BX_CPP_INLINE void
bx_cpu_c::set_SF(Boolean val) {
    bx_cpu. lf_flags_status &= 0xf0ffff;
    bx_cpu. eflags.sf = val;
    }


    BX_CPP_INLINE void
bx_cpu_c::set_OF(Boolean val) {
    bx_cpu. lf_flags_status &= 0x0fffff;
    bx_cpu. eflags.of = val;
    }

    BX_CPP_INLINE void
bx_cpu_c::set_PF(Boolean val) {
    bx_cpu. lf_flags_status &= 0xffff0f;
    bx_cpu. lf_pf = val;
    }

    BX_CPP_INLINE void
bx_cpu_c::set_PF_base(Bit8u val) {
    bx_cpu. eflags.pf_byte = val;
    bx_cpu. lf_flags_status = (bx_cpu. lf_flags_status & 0xffff0f) | BX_LF_MASK_P;
    }


#define SET_FLAGS_OSZAPC_8(op1, op2, result, ins) { \
    bx_cpu. oszapc.op1_8 = op1; \
    bx_cpu. oszapc.op2_8 = op2; \
    bx_cpu. oszapc.result_8 = result; \
    bx_cpu. oszapc.instr = ins; \
    bx_cpu. lf_flags_status = BX_LF_MASK_OSZAPC; \
    }

#define SET_FLAGS_OSZAPC_8_CF(op1, op2, result, ins, last_CF) { \
    bx_cpu. oszapc.op1_8 = op1; \
    bx_cpu. oszapc.op2_8 = op2; \
    bx_cpu. oszapc.result_8 = result; \
    bx_cpu. oszapc.instr = ins; \
    bx_cpu. oszapc.prev_CF = last_CF; \
    bx_cpu. lf_flags_status = BX_LF_MASK_OSZAPC; \
    }

#define SET_FLAGS_OSZAPC_16(op1, op2, result, ins) { \
    bx_cpu. oszapc.op1_16 = op1; \
    bx_cpu. oszapc.op2_16 = op2; \
    bx_cpu. oszapc.result_16 = result; \
    bx_cpu. oszapc.instr = ins; \
    bx_cpu. lf_flags_status = BX_LF_MASK_OSZAPC; \
    }

#define SET_FLAGS_OSZAPC_16_CF(op1, op2, result, ins, last_CF) { \
    bx_cpu. oszapc.op1_16 = op1; \
    bx_cpu. oszapc.op2_16 = op2; \
    bx_cpu. oszapc.result_16 = result; \
    bx_cpu. oszapc.instr = ins; \
    bx_cpu. oszapc.prev_CF = last_CF; \
    bx_cpu. lf_flags_status = BX_LF_MASK_OSZAPC; \
    }

#define SET_FLAGS_OSZAPC_32(op1, op2, result, ins) { \
    bx_cpu. oszapc.op1_32 = op1; \
    bx_cpu. oszapc.op2_32 = op2; \
    bx_cpu. oszapc.result_32 = result; \
    bx_cpu. oszapc.instr = ins; \
    bx_cpu. lf_flags_status = BX_LF_MASK_OSZAPC; \
    }

#define SET_FLAGS_OSZAPC_32_CF(op1, op2, result, ins, last_CF) { \
    bx_cpu. oszapc.op1_32 = op1; \
    bx_cpu. oszapc.op2_32 = op2; \
    bx_cpu. oszapc.result_32 = result; \
    bx_cpu. oszapc.instr = ins; \
    bx_cpu. oszapc.prev_CF = last_CF; \
    bx_cpu. lf_flags_status = BX_LF_MASK_OSZAPC; \
    }


#define SET_FLAGS_OSZAP_8(op1, op2, result, ins) { \
    bx_cpu. oszap.op1_8 = op1; \
    bx_cpu. oszap.op2_8 = op2; \
    bx_cpu. oszap.result_8 = result; \
    bx_cpu. oszap.instr = ins; \
    bx_cpu. lf_flags_status = (bx_cpu. lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP; \
    }

#define SET_FLAGS_OSZAP_16(op1, op2, result, ins) { \
    bx_cpu. oszap.op1_16 = op1; \
    bx_cpu. oszap.op2_16 = op2; \
    bx_cpu. oszap.result_16 = result; \
    bx_cpu. oszap.instr = ins; \
    bx_cpu. lf_flags_status = (bx_cpu. lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP; \
    }

#define SET_FLAGS_OSZAP_32(op1, op2, result, ins) { \
    bx_cpu. oszap.op1_32 = op1; \
    bx_cpu. oszap.op2_32 = op2; \
    bx_cpu. oszap.result_32 = result; \
    bx_cpu. oszap.instr = ins; \
    bx_cpu. lf_flags_status = (bx_cpu. lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP; \
    }

#define SET_FLAGS_OxxxxC(new_of, new_cf) { \
    bx_cpu. eflags.of = (Boolean) new_of; \
    bx_cpu. eflags.cf = (Boolean) new_cf; \
    bx_cpu. lf_flags_status &= 0x0ffff0; \
    /* ??? could also mark other bits undefined here */ \
    }






extern const Boolean bx_parity_lookup[256];

#define BX_REPE_PREFIX  10
#define BX_REPNE_PREFIX 11



#define BX_TASK_FROM_JUMP         10
#define BX_TASK_FROM_CALL_OR_INT  11
#define BX_TASK_FROM_IRET         12


//
// For decoding...
//

// If the Immediate bit is set, the lowest 3 bits of the attribute
// specify which kinds of immediate data a required by instruction.

#define BxImmediate         0x000f // bits 3..0: any immediate
#define BxImmediate_Ib      0x0001 // 8 bits regardless
#define BxImmediate_Ib_SE   0x0002 // sign extend to OS size
#define BxImmediate_Iv      0x0003 // 16 or 32 depending on OS size
#define BxImmediate_Iw      0x0004 // 16 bits regardless
#define BxImmediate_IvIw    0x0005 // call_Ap
#define BxImmediate_IwIb    0x0006 // enter_IwIb
#define BxImmediate_O       0x0007 // mov_ALOb, mov_ObAL, mov_eAXOv, mov_OveAX
#define BxImmediate_BrOff8  0x0008 // Relative branch offset byte
#define BxImmediate_BrOff16 0x0009 // Relative branch offset word
#define BxImmediate_BrOff32 BxImmediate_Iv

#define BxPrefix          0x0010 // bit  4
#define BxAnother         0x0020 // bit  5
#define BxRepeatable      0x0040 // bit  6
#define BxRepeatableZF    0x0080 // bit  7
#define BxGroupN          0x0100 // bits 8
#define BxGroup1          BxGroupN
#define BxGroup2          BxGroupN
#define BxGroup3          BxGroupN
#define BxGroup4          BxGroupN
#define BxGroup5          BxGroupN
#define BxGroup6          BxGroupN
#define BxGroup7          BxGroupN
#define BxGroup8          BxGroupN
#define BxGroup9          BxGroupN
#define BxGroupa          BxGroupN

#if BX_DEBUGGER
typedef enum _show_flags {
      Flag_call = 0x1,
      Flag_ret = 0x2,
      Flag_int = 0x4,
      Flag_iret = 0x8,
      Flag_intsig = 0x10
} show_flags_t;
#endif

#endif  // #ifndef BX_CPU_H
