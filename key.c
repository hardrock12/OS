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

/*
 * 
 * Unicode code point (if applicable)
Key code
Pressed/released flag
Various other key states (shift, alt, control, etc)
Various "toggle" states (CapsLock, ScrollLock, NumberLock, etc)*/
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





static void status();

static u8int checkstatus(u16int port,u8int bit );
void install_kb();





/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
Scan code	 Key	 Scan code	 Key	 Scan code	 Key	 Scan code	 Key
0x01	 escape pressed	 0x02	 1 pressed	 0x03	 2 pressed
0x04	 3 pressed	 0x05	 4 pressed	 0x06	 5 pressed	 0x07	 6 pressed
0x08	 7 pressed	 0x09	 8 pressed	 0x0A	 9 pressed	 0x0B	 0 (zero) pressed
0x0C	 - pressed	 0x0D	 = pressed	 0x0E	 backspace pressed	 0x0F	 tab pressed
0x10	 Q pressed	 0x11	 W pressed	 0x12	 E pressed	 0x13	 R pressed
0x14	 T pressed	 0x15	 Y pressed	 0x16	 U pressed	 0x17	 I pressed
0x18	 O pressed	 0x19	 P pressed	 0x1A	 [ pressed	 0x1B	 ] pressed
0x1C	 enter pressed	 0x1D	 left control pressed	 0x1E	 A pressed	 0x1F	 S pressed
0x20	 D pressed	 0x21	 F pressed	 0x22	 G pressed	 0x23	 H pressed
0x24	 J pressed	 0x25	 K pressed	 0x26	 L pressed	 0x27	 ; pressed
0x28	 ' (single quote) pressed	 0x29	 ` (back tick) pressed	 0x2A	 left shift pressed	 0x2B	 \ pressed
0x2C	 Z pressed	 0x2D	 X pressed	 0x2E	 C pressed	 0x2F	 V pressed
0x30	 B pressed	 0x31	 N pressed	 0x32	 M pressed	 0x33	 , pressed
0x34	 . pressed	 0x35	 / pressed	 0x36	 right shift pressed	 0x37	 (keypad) * pressed
0x38	 left alt pressed	 0x39	 space pressed	 0x3A	 CapsLock pressed	 0x3B	 F1 pressed
0x3C	 F2 pressed	 0x3D	 F3 pressed	 0x3E	 F4 pressed	 0x3F	 F5 pressed
0x40	 F6 pressed	 0x41	 F7 pressed	 0x42	 F8 pressed	 0x43	 F9 pressed
0x44	 F10 pressed	 0x45	 NumberLock pressed	 0x46	 ScrollLock pressed	 0x47	 (keypad) 7 pressed
0x48	 (keypad) 8 pressed	 0x49	 (keypad) 9 pressed	 0x4A	 (keypad) - pressed	 0x4B	 (keypad) 4 pressed
0x4C	 (keypad) 5 pressed	 0x4D	 (keypad) 6 pressed	 0x4E	 (keypad) + pressed	 0x4F	 (keypad) 1 pressed
0x50	 (keypad) 2 pressed	 0x51	 (keypad) 3 pressed	 0x52	 (keypad) 0 pressed	 0x53	 (keypad) . pressed
0x57	 F11 pressed
0x58	 F12 pressed						
0x81	 escape released	 0x82	 1 released	 0x83	 2 released
0x84	 3 released	 0x85	 4 released	 0x86	 5 released	 0x87	 6 released
0x88	 7 released	 0x89	 8 released	 0x8A	 9 released	 0x8B	 0 (zero) released
0x8C	 - released	 0x8D	 = released	 0x8E	 backspace released	 0x8F	 tab released
0x90	 Q released	 0x91	 W released	 0x92	 E released	 0x93	 R released
0x94	 T released	 0x95	 Y released	 0x96	 U released	 0x97	 I released
0x98	 O released	 0x99	 P released	 0x9A	 [ released	 0x9B	 ] released
0x9C	 enter released	 0x9D	 left control released	 0x9E	 A released	 0x9F	 S released
0xA0	 D released	 0xA1	 F released	 0xA2	 G released	 0xA3	 H released
0xA4	 J released	 0xA5	 K released	 0xA6	 L released	 0xA7	 ; released
0xA8	 ' (single quote) released	 0xA9	 ` (back tick) released	 0xAA	 left shift released	 0xAB	 \ released
0xAC	 Z released	 0xAD	 X released	 0xAE	 C released	 0xAF	 V released
0xB0	 B released	 0xB1	 N released	 0xB2	 M released	 0xB3	 , released
0xB4	 . released	 0xB5	 / released	 0xB6	 right shift released	 0xB7	 (keypad) * released
0xB8	 left alt released	 0xB9	 space released	 0xBA	 CapsLock released	 0xBB	 F1 released
0xBC	 F2 released	 0xBD	 F3 released	 0xBE	 F4 released	 0xBF	 F5 released
0xC0	 F6 released	 0xC1	 F7 released	 0xC2	 F8 released	 0xC3	 F9 released
0xC4	 F10 released	 0xC5	 NumberLock released	 0xC6	 ScrollLock released	 0xC7	 (keypad) 7 released
0xC8	 (keypad) 8 released	 0xC9	 (keypad) 9 released	 0xCA	 (keypad) - released	 0xCB	 (keypad) 4 released
0xCC	 (keypad) 5 released	 0xCD	 (keypad) 6 released	 0xCE	 (keypad) + released	 0xCF	 (keypad) 1 released
0xD0	 (keypad) 2 released	 0xD1	 (keypad) 3 released	 0xD2	 (keypad) 0 released	 0xD3	 (keypad) . released
0xD7	 F11 released
0xD8	 F12 released						
0xE0, 0x1C	 (keypad) enter pressed	 0xE0, 0x1D	 right control pressed				
0xE0, 0x35	 (keypad) / pressed				
0xE0, 0x38	 right alt (or altGr) pressed						
0xE0, 0x47	 home pressed
0xE0, 0x48	 cursor up pressed	 0xE0, 0x49	 page up pressed			 0xE0, 0x4B	 cursor left pressed
0xE0, 0x4D	 cursor right pressed			 0xE0, 0x4F	 end pressed
0xE0, 0x50	 cursor down pressed	 0xE0, 0x51	 page down pressed	 0xE0, 0x52	 insert pressed	 0xE0, 0x53	 delete pressed
0xE0, 0x5B	 left GUI pressed
0xE0, 0x5C	 right GUI pressed	 0xE0, 0x5D	 "apps" pressed				
0xE0, 0x9C	 (keypad) enter released	 0xE0, 0x9D	 right control released				
0xE0, 0xB5	 (keypad) / released				
0xE0, 0xB8	 right alt (or altGr) released						
0xE0, 0xC7	 home released
0xE0, 0xC8	 cursor up released	 0xE0, 0xC9	 page up released			 0xE0, 0xCB	 cursor left released
0xE0, 0xCD	 cursor right released			 0xE0, 0xCF	 end released
0xE0, 0xD0	 cursor down released	 0xE0, 0xD1	 page down released	 0xE0, 0xD2	 insert released	 0xE0, 0xD3	 delete released
0xE0, 0xDB	 left GUI released
0xE0, 0xDC	 right GUI released	 0xE0, 0xDD	 "apps" released				
0xE0, 0x2A, 0xE0, 0x37	 print screen pressed
0xE0, 0xB7, 0xE0, 0xAA	 print screen released
0xE1, 0x1D, 0x45, 0xE1, 0x9D, 0xC5	 pause pressed				



*////





static void key_handler(registers_t regs)
{
monitor_write("ar1:");
monitor_write_hex(inb(p60));
monitor_write("\n");
monitor_write_hex(inb(p60));

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
  
  char ch[]={0,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t','q','w','e','r','t','y','u','i','o','p','[',']',0,0,'a','s','d','f','g','h','j','k','l',';','\'','~',0,'z','x','c','v','b','n','m',',','.','/',0,' '};;
  
  
  
register_interrupt_handler(IRQ1,&key_handler);


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
  u16int c=0x1;
while(c=inb(0x60)&&inb(0x60)!=ACK){}
monitor_write_hex(c);
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
