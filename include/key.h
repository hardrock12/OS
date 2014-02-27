#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED
#include "common.h"
void installkb();
u8int scancode;
u8int keyyed;
u8int read_configura();
u8int   get_status_byte(int x);
#endif // KEY_H_INCLUDED
