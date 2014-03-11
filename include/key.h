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
struct keydata {
  char ch;
  u8int keystate; //key press/release
u8int ctrl_key_state;
u8int ctrl_key_side;

u8int key_togle_state; 

};

struct vkeys {
  
char* name;
u8int scancode;
u8int side;
char unicode;

 
}keys[300];
    
#endif // KEY_H_INCLUDED
