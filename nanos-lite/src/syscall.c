#include "common.h"
#include "syscall.h"
#include "fs.h"
#include "proc.h"

void naive_uload(PCB *pcb, const char *filename);

static inline int32_t sys_execve(const char *pathname, char *const argv[], char *const envp[]) {
  naive_uload(NULL, pathname);
  return 0;
}

_Context* do_syscall(_Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;

  switch (a[0]) {
    case SYS_exit: sys_execve("/bin/init", NULL, NULL); break;
    case SYS_yield: _yield(); c->GPRx = 0; break;
    case SYS_open: c->GPRx = fs_open((void *)a[1], a[2], a[3]); break;
    case SYS_read: c->GPRx = fs_read(a[1], (void *)a[2], a[3]); break;
    case SYS_write: 
      // Log("write\n");
      // if(a[1]==1||a[1]==2){
			// 	  for(int i=0;i<a[3];i++)
			// 		  _putc(*(char*)(a[2]+i));
			// 	  c->GPRx=a[3];
      // } break;
      c->GPRx = fs_write(a[1], (void *)a[2], a[3]) ; break;
    case SYS_close: c->GPRx = fs_close(a[1]); break;
    case SYS_lseek: c->GPRx = fs_lseek(a[1], a[2], a[3]); break;
    case SYS_brk: c->GPRx = 0; break;
    case SYS_execve: c->GPRx = sys_execve((void *)a[1], (char *const *)(void *)a[2], (char *const *)(void *)a[3]); break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

  return NULL;
}
