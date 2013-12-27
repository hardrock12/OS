// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "multiboot.h"
#include "common.h"

#if CHAPTER >= 3
#include "monitor.h"
#endif
#if CHAPTER >= 4
#include "gdt.h"
#include "idt.h"
#endif
#if CHAPTER >= 5
#include "timer.h"
#endif
#if CHAPTER >= 6
#include "elf.h"
#endif
#if CHAPTER >= 7
#include "pmm.h"
#include "vmm.h"
#endif
#if CHAPTER >= 8
#include "heap.h"
#endif
#if CHAPTER >= 9
#include "thread.h"
#endif
#if CHAPTER >= 10
#include "lock.h"
#endif
#if CHAPTER >= 11
#include "keyboard.h"
#endif

#if CHAPTER >= 6
elf_t kernel_elf;
#endif

#if CHAPTER == 9
int fn(void *arg)
{
  for(;;) {
    printk("a");
  }
  return 6;
}
#endif

#if CHAPTER >= 10
spinlock_t lock = SPINLOCK_UNLOCKED;

int fn(void *arg)
{
  for(;;) {
    int i;
    spinlock_lock(&lock);
    for(i = 0; i < 80; i++)
      printk("a");
    spinlock_unlock(&lock);
  }
  return 6;
}
#endif

int kernel_main(multiboot_t *mboot_ptr)
{
#if CHAPTER >= 3
  monitor_clear();
#endif

#if CHAPTER == 3 || CHAPTER == 4
  monitor_write("Hello, world!\n");
#endif

#if CHAPTER >= 4
  init_gdt ();
  init_idt ();
#endif
#if CHAPTER == 4
  asm volatile("int $0x3");
#endif

#if CHAPTER >= 5
  init_timer (20);
#endif
#if CHAPTER >= 7
  init_pmm (mboot_ptr->mem_upper);
  init_vmm ();
#endif
#if CHAPTER >= 8
  init_heap ();
#endif

#if CHAPTER >= 7
  // Find all the usable areas of memory and inform the physical memory manager about them.
  uint32_t i = mboot_ptr->mmap_addr;
  while (i < mboot_ptr->mmap_addr + mboot_ptr->mmap_length)
  {
    mmap_entry_t *me = (mmap_entry_t*) i;

    // Does this entry specify usable RAM?
    if (me->type == 1)
    {
      uint32_t j;
      // For every page in this entry, add to the free page stack.
      for (j = me->base_addr_low; j < me->base_addr_low+me->length_low; j += 0x1000)
      {
        pmm_free_page (j);
      }
    }

    // The multiboot specification is strange in this respect - the size member does not include "size" itself in its calculations,
    // so we must add sizeof (uint32_t).
    i += me->size + sizeof (uint32_t);
  }
#endif
#if CHAPTER >= 6
  kernel_elf = elf_from_multiboot (mboot_ptr);
#endif
#if CHAPTER >= 9
  asm volatile ("sti");
  init_scheduler (init_threading ());
#endif
#if CHAPTER == 9
  uint32_t *stack = kmalloc (0x400) + 0x3F0;

  thread_t *t = create_thread(&fn, (void*)0x567, stack);
  for(;;) {
    printk("b");
  }

#endif

#if CHAPTER == 10
  uint32_t *stack = kmalloc (0x400) + 0x3F0;

  thread_t *t = create_thread(&fn, (void*)0x567, stack);
  for(;;) {
    int i;
    spinlock_lock(&lock);
    for(i = 0; i < 80; i++)
      printk("b");
    spinlock_unlock(&lock);
  }

#endif

#if CHAPTER == 5
  asm volatile("sti");
#endif
#if CHAPTER == 6
  panic ("Testing panic mechanism");
#endif
#if CHAPTER >= 11
  init_keyboard_driver();
#if CHAPTER == 11
  for(;;)
  {
      char c = keyboard_getchar();
      if (c)
          monitor_put(c);
  }       
#endif
#endif
#if CHAPTER >= 3
  for (;;);
#endif

  return 0xdeadbeef;
}
