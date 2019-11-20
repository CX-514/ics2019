#include "common.h"
#include "syscall.h"

_Context* do_syscall(_Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;

  switch (a[0]) {
    // case SYS_exit: _halt(a[1]); break;
    // case SYS_yield: _yield();  break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

  return NULL;
}
