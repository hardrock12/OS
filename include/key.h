#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED
#include "common.h"
void installkb();
u8int scancode;
u8int keyyed;
u8int read_configura();
void ackk();
void write_config(u8int config_byte);
u8int   get_status_byte(int x);
void switch_comand_ps();
#endif // KEY_H_INCLUDED
