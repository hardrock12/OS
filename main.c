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

    initialise_paging();


init_timer(50);

install_kb();

monitor_write("arjun");
//u32int foo=0x21F;
/*monitor_write_dec((encode(foo,32)));
s("                                            \n");
monitor_write_dec(encode(encode(foo,32),32));
s("                                            \n");
monitor_write_dec(encode(encode(encode(foo,32),32),32));
/*/
//identify();

u32int com=0,dat=0;
int flag=0;
int in=0;
/*while(in<10)
{
outb(0x60,0xED);

monitor_write_hex(inb(0x60));
monitor_write("\n");
monitor_write_hex(inb(0x60));
outb(0x60,0x0+(in%3));


}*/



outb(0x64,0x20);
while(1)
{

if(inb(0x64)&&0x200)
{
monitor_write_hex(inb(0x60));

}
}


while(flag==0)

{

if(getstored()!=-1){
monitor_write("command:");

monitor_write_hex(getstored());
}

}


    return 0;
}
