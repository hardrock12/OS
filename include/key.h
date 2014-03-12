#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED
#include "common.h"
void installkb();
void installl_zero();
u8int scancode;
u8int keyyed;
u8int read_configura();
void ackk();
void write_config(u8int config_byte);
u8int   get_status_byte(int x);
void switch_comand_ps();
u16int pic_get_irr(void);
/* Returns the combined value of the cascaded PICs in-service register */
u16int pic_get_isr(void);

void IRQ_set_mask(unsigned char IRQline) ;

 
void IRQ_clear_mask(unsigned char IRQline);

 /* * 0xD7	 F11 released
0xD8	 F12 released						
		
0xE0, 0x35	 (keypad) / pressed				
					
0xE0, 0x47	 home pressed
	
			 0xE0, 0x4F	 end pressed
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
0xE1, 0x1D, 0x45, 0xE1, 0x9D, 0xC5	 pause pressed	/**/
enum  Specialkeys_PRESS{
  ESC=0X1
  ,F1=0X57
  ,F2=0X58
  ,F3=0X3D
  ,F4=0X3E
  ,F5=0X3F
  ,F6=0X40
  ,F7=0X41
  ,F8=0X42
  ,F9=0X43
  ,F10=0X44
  
  ,F11=0XD7
  ,F12=0XD8
  ,L_CTRL
  ,L_ALT
  ,R_ALT=0X38
  ,R_CTRL=0X1D
  ,R_SHIFT
  ,L_SHIFT
  ,DELETE=0X53
  ,HOME=0X47
  ,INSERT=0X52
  ,END=0X4F
  ,PAGUP=0X48
  ,PAGD=0X51
  ,L_ENTER
  ,R_ENTER=0X1C
  ,ARROW_UP=0X48
  ,ARROW_DOW=0X50
  ,ARROW_L=0X4B
  ,ARROW_RIGHT=0X4D
  
  ,SRL_L=0X46
  ,CAP_L=0X3A
  ,NUM_L=0X45
  ,PAUSE};






struct keydata {
  char ch;
  u8int keystate; //key press/release
u16int ctrl_key_state;              //left ctrl,left alt ,left delete,right alt,right ctrl
u8int ctrl_key_side;
u8int key_togle_state; 
enum Specialkeys_PRESS special;

};




struct vkeys {
  
char* name;
u8int scancode;
u8int side;
char unicode;

 
}keys[300];
    
#endif // KEY_H_INCLUDED
