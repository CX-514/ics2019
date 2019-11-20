#ifndef __ARCH_H__
#define __ARCH_H__

struct _Context {
  /*uintptr_t esi, ebx, eax, eip, edx, eflags, ecx, cs, esp, edi, ebp;
  struct _AddressSpace *as;
  int irq;*/
  struct _AddressSpace *as;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t irq;
  uint32_t eip, cs, eflags;
};

#define GPR1 eax
#define GPR2 ebx
#define GPR3 ecx
#define GPR4 edx
#define GPRx eax

#endif
