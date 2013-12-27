// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "multiboot.h"
#include "common.h"

#include "monitor.h"

int kernel_main(multiboot_t *mboot_ptr)
{
  monitor_clear();

  monitor_write("Hello, world!\n");

  for (;;);

  return 0xdeadbeef;
}
