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

#define PIC1_CMD                    0x20
#define PIC1_DATA                   0x21
#define PIC2_CMD                    0xA0
#define PIC2_DATA                   0xA1
#define PIC_READ_IRR                0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                0x0b    /* OCW3 irq service next CMD read */
 
 
 
#include "key.h"
#include "common.h"
#include "monitor.h"
#include "isr.h"
/* Helper func */


// cleart mask



void IRQ_set_mask(unsigned char IRQline) {
    u16int port;
    u8int value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}
 
void IRQ_clear_mask(unsigned char IRQline) {
    u16int port;
    u8int value;
    
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}


//



static u16int __pic_get_irq_reg(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_CMD, ocw3);
    outb(PIC2_CMD, ocw3);
    return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
u16int pic_get_irr(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
u16int pic_get_isr(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}

//static void status();




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
{
monitor_write("ar1:");

    /* Read from the keyboard's data buffer */

}



static void zer(registers_t regs)
{
  
  monitor_write("divisin by zero"); 
  
}
void installl_zero()
{
  
  register_interrupt_handler(0x0,&zer);
}

void install_kb()
{ // status();
//outb(p60,0xED);
//outb(p60,0x7);
register_interrupt_handler(IRQ12,&key_handler);


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
/// writes configuratn
void write_config(u8int config_byte)
{
outb(p64,0x60);
outb(p60,config_byte);



}




// acknowledge
 void ackk()
{
while(inb(0x60)!=ACK){}
return;


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
 void switch_comand_ps()
{
    outb(p64,0XD4);//0 FOR SECOND PORT


}





















static void status()
{
 monitor_write("entered");
monitor_write_hex(inb(p64));
   monitor_write_hex(inb(p60));



}
