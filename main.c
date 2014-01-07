// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "monitor.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "paging.h"
#include "hard.h"
#include "common.h"
#include "runtimecoding.h"

int main(struct multiboot *mboot_ptr)
{
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
    monitor_clear();
    u32int a = kmalloc(8);
    initialise_paging();

    u32int b = kmalloc(8);
    u32int c = kmalloc(8);
    monitor_write("a: ");
    monitor_write_hex(a);
    monitor_write(", b: ");
    monitor_write_hex(b);
    monitor_write("\nc: ");
    monitor_write_hex(c);
init_timer(50);
    kfree(c);
    kfree(b);
    u32int d = kmalloc(12);
    monitor_write(", d: ");
    monitor_write_hex(d);
install_kb();


u32int foo=0x21F;
monitor_write_dec((encode(foo,32)));
s("                                            \n");
monitor_write_dec(encode(encode(foo,32),32));
s("                                            \n");
monitor_write_dec(encode(encode(encode(foo,32),32),32));
//identify();
    return 0;
}
