// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "multiboot.h"
#include "common.h"

#include "monitor.h"
#include "gdt.h"
#include "idt.h"

int kernel_main(multiboot_t *mboot_ptr)
{
  monitor_clear();

  init_gdt ();
  init_idt ();
  asm volatile("int $0x3");

  for (;;);

  return 0xdeadbeef;
}
