#ifndef __SYSTEM_H
#define __SYSTEM_H

/* MAIN.C */
extern void *memcpy(void *dest, const void *src, int count);
extern void *memset(void *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern unsigned char inportb (unsigned short _port);
extern int strlen(const char *str);
extern void outportb (unsigned short _port, unsigned char _data)
void cls();
void putch(unsigned char c);
void puts(unsigned char *str);
void settextcolor(unsigned char forecolor, unsigned char backcolor);
 void init_video();

#endif
