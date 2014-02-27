// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "monitor.h"
#include "descriptor_tables.h"
#include "timer.h"
//#include "paging.h"
//#include "hard.h"
#include "common.h"
//#include "runtimecoding.h"

int main(struct multiboot *mboot_ptr)
{
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
    monitor_clear();

//    initialise_paging();


init_timer(50);

install_kb();

monitor_write("arjun");



monitor_write(":                 ");

pbyte(read_configura());
monitor_write("cx");
pbyte(inb(0x60));
monitor_write("config");
pbyte(read_configura());


monitor_write("editing configuration file");
write_config(read_configura()|0x8);

monitor_write("arjunDf:");
pbyte(read_configura());



    return 0;
}
