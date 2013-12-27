// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "multiboot.h"
#include "common.h"

#include "monitor.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "elf.h"

elf_t kernel_elf;

int kernel_main(multiboot_t *mboot_ptr)
{
  monitor_clear();

  init_gdt ();
  init_idt ();

  init_timer (20);

  kernel_elf = elf_from_multiboot (mboot_ptr);

  panic ("Testing panic mechanism");
  for (;;);

  return 0xdeadbeef;
}
