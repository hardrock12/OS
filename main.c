// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "monitor.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "key.h"

int main(struct multiboot *mboot_ptr)
{
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
    monitor_clear();
    // Write out a sample string
    monitor_write("Hello, world!\n");

  

   asm volatile("sti");
   IRQ_set_mask(0);
     IRQ_clear_mask(0);
   // init_timer(50);
    int x=pic_get_irr();
    monitor_write_dec(x);
       x=pic_get_isr();
    monitor_write_dec(x);
install_kb();
installl_zero();
x/=0;
    return 0;
}
