#include "proc.h"
#include <elf.h>
#include <fs.h>

#ifdef __ISA_AM_NATIVE__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

size_t ramdisk_read(void *buf, size_t offset, size_t len);

static uintptr_t loader(PCB *pcb, const char *filename) {
  // Elf_Ehdr ehdr;
  // ramdisk_read(&ehdr, 0, sizeof(Elf_Ehdr));
  // Elf_Phdr phdr[ehdr.e_phnum];
  // ramdisk_read(&phdr, ehdr.e_ehsize, sizeof(Elf_Phdr)*ehdr.e_phnum);
  // for (size_t i = 0; i < ehdr.e_phnum; i++) {
  //   if (phdr[i].p_type == PT_LOAD) {
  //     ramdisk_read((void *)phdr[i].p_vaddr, phdr[i].p_offset, phdr[i].p_memsz);
  //     memset((void *)(phdr[i].p_vaddr + phdr[i].p_filesz), 0, phdr[i].p_memsz - phdr[i].p_filesz);
  //   }
  // }
  // return ehdr.e_entry;
  // int fd = fs_open(filename, 0, 0);
  // assert(fd == -1);
  // Elf_Ehdr ehdr;
  // fs_read(fd, (void *)&ehdr, sizeof(Elf_Ehdr));
  // Elf_Phdr phdr[ehdr.e_phnum];
  // for (size_t i = 0; i < ehdr.e_phnum; i++) {
  //   fs_lseek(fd, ehdr.e_phoff+i*ehdr.e_phentsize, SEEK_SET);
  //   fs_read(fd, (void *)&phdr[i], ehdr.e_phentsize);
  //   if (phdr[i].p_type == PT_LOAD) {
  //     fs_lseek(fd, phdr[i].p_offset, SEEK_SET);
  //     fs_read(fd, (void *)&phdr[i].p_vaddr, phdr[i].p_filesz);
  //     memset((void *)(phdr[i].p_vaddr + phdr[i].p_filesz), 0, phdr[i].p_memsz - phdr[i].p_filesz);
  //   }
  // }
  // fs_close(fd);
  // return ehdr.e_entry;
  int fd = fs_open(filename, 0, 0);
  if (fd == -1) {
    panic("loader: can't open file %s!", filename);
  }

  Elf_Ehdr elf_header;
  fs_read(fd, (void *)&elf_header, sizeof(Elf_Ehdr));
  if (memcmp(elf_header.e_ident, ELFMAG, SELFMAG))
    panic("file %s ELF format error!", filename);

  for (size_t i = 0; i < elf_header.e_phnum; ++i) {
    Elf_Phdr phdr;
    fs_lseek(fd, elf_header.e_phoff + elf_header.e_phentsize * i, SEEK_SET);
    fs_read(fd, (void *)&phdr, elf_header.e_phentsize);
    if (phdr.p_type == PT_LOAD) {
      fs_lseek(fd, phdr.p_offset, SEEK_SET);
      fs_read(fd, (void *)phdr.p_vaddr, phdr.p_filesz);
      memset((void *)(phdr.p_vaddr + phdr.p_filesz), 0, phdr.p_memsz - phdr.p_filesz);
    }
  }

  fs_close(fd);

return elf_header.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %x", entry);
  ((void(*)())entry) ();
}

void context_kload(PCB *pcb, void *entry) {
  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _kcontext(stack, entry, NULL);
}

void context_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);

  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _ucontext(&pcb->as, stack, stack, (void *)entry, NULL);
}
