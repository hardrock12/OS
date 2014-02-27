#define ACK 0xFA
#define RESND 0xFE
#define p64 0x64
#define p60 0x60

/// PS/2 channels
#define dis_2 0xA7	//Disable second PS/2 port (only if 2 PS/2 ports supported)	None
#define en_2 0xA8	//Enable second PS/2 port (only if 2 PS/2 ports supported)	None

#define dis_1 0xAD	//Disable first PS/2 port	None
#define en_1 0xAE	//Enable first PS/2 port	None
/*0xC0	Read controller input port	Unknown (none of these bits have a standard/defined purpose)
0xC1	Copy bits 0 to 3 of input port to status bits 4 to 7	None
0xC2	Copy bits 4 to 7 of input port to status bits 4 to 7	None
0xD0	Read Controller Output Port	Controller Output Port (see below)
0xD1	Write next byte to Controller Output Port (see below)
Note: Check if output buffer is empty first
None*/
//0xD2	Write next byte to first PS/2 port output buffer (only if 2 PS/2 ports supported)
//(makes it look like the byte written was received from the first PS/2 port)
//None
//0xD3	Write next byte to second PS/2 port output buffer (only if 2 PS/2 ports supported)
//(makes it look like the byte written was received from the second PS/2 port)
//None
//0xD4	Write next byte to second PS/2 port input buffer (only if 2 PS/2 ports supported)
//(sends next byte to the second PS/2 port)
//None
//0xF0 to 0xFF	Pulse output line low for 6 ms. Bits 0 to 3 are used as a mask (0 = pulse line, 1 = don't pulse line) and correspond to 4 different output lines.
//Note: Bit 0 corresponds to the "reset" line. The other output lines don't have a standard/defined purpose.
//None
///



//static void status();



#include "key.h"
#include "common.h"
#include "monitor.h"
#include "isr.h"
u8int kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',	 /* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	 /* Enter key */
    0,	 /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,	 /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',	 /* 49 */
  'm', ',', '.', '/',   0,	 /* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
static void status();

static u8int checkstatus(u16int port,u8int bit );
void install_kb();

static void key_handler(registers_t regs)
{monitor_write("got");
keyyed=1;

    /* Read from the keyboard's data buffer */
    scancode = inb(0x60);


    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        keyyed=0;/* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        //printchar(kbdus[scancode]);
        monitor_put(kbdus[scancode]);
        if(kbdus[scancode]!='k'){
getint(scancode);}
else{
getint(-1);

}


    }

}





void install_kb()
{ // status();
//outb(p60,0xED);
//outb(p60,0x7);
register_interrupt_handler(IRQ1,key_handler);


//u32int i;
//for( i=20000;i>0;i--);

//outb(p60,0xF5);
//while (checkstatus(p64,0)==0)
//{}/
//monitor_write_hex(inb(p60));



//monitor_write("done.");


}
static u8int checkstatus(u16int port,u8int bit)
{
if((inb(port)>>bit)==1)
{return 1;}
else{return 0;}

}

static  void DISABLEdevice(int x)
{ if(x==2)
{
      outb(p64,0XA7);//0 FOR SECOND PORT
      }
      else{

      outb(p64,0XAD);
      }

}
u8int read_configura()
{outb(p64,0x20);
while(get_status_byte(0)!=1)
{}
return inb(0x60);


}
u8int   get_status_byte(int x)
{
u8int i=inb(0x64);
if((i>>x)&(0x1))
return 1;
else
return 0;


}
static void switch_comand_ps(int x)
{

if(x==2)
{
      outb(p64,0XD4);//0 FOR SECOND PORT
      }


}





















static void status()
{
 monitor_write("entered");
monitor_write_hex(inb(p64));
   monitor_write_hex(inb(p60));



}
