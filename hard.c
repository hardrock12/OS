#include "hard.h"
#include "common.h"
#define sec 0x1F2

void identify()
{
//source : osdev
/*To use the IDENTIFY command, select a target drive by sending 0xA0 for the master drive,
 or 0xB0 for the slave, to the "drive select" IO port. On the Primary bus, this would be port 0x1F6.
 Then set the Sectorcount, LBAlo, LBAmid, and LBAhi IO ports to 0 (port 0x1F2 to 0x1F5).
 Then send the IDENTIFY command (0xEC) to the Command IO port (0x1F7).
  Then read the Status port (0x1F7) again.
  If the value read is 0, the drive does not exist. For any other value: poll the Status port (0x1F7)
  until bit 7 (BSY, value = 0x80) clears. Because of some ATAPI drives that do not follow spec,
  at this point you need to check the LBAmid and LBAhi ports (0x1F4 and 0x1F5) to see if they are non-zero.
   If so, the drive is not ATA, and you should stop polling. Otherwise, continue polling one of the Status
   ports until bit 3 (DRQ, value = 8) sets, or until bit 0 (ERR, value = 1) sets.

At that point, if ERR is clear, the data is ready to read from the Data port (0x1F0)
. Read 256 words, and store them.

*/


/*// source:osdev

Bit	 Abbreviation	 Function
0	 ERR	 Indicates an error occurred. Send a new command to clear it (or nuke it with a Software Reset).
3	 DRQ	 Set when the drive has PIO data to transfer, or is ready to accept PIO data.
4	 SRV	 Overlapped Mode Service Request.
5	 DF	 Drive Fault Error (does not set ERR).
6	 RDY	 Bit is clear when drive is spun down, or after an error. Set otherwise.
7	 BSY	 Indicates the drive is preparing to send/receive data (wait for it to clear). In case of 'hang' (it never clears), do a software reset.
*/
u16int id[256];
//outb(0x1F6,0xB0);
monitor_clear();
  outb(0x1F6,0xA0); //selecteing master drive
  int i=0;
  while(i<4)
  {outb(sec+i,0x0);i++;};
  outb(0x1F2,0xEC);
  int flag=0 ;



  monitor_write_hex(inb(0x1F7));
  while(flag==0)
  {
 if(1|| bitque(inb(0x1F7),0,7)&&(bitque(inb(0x1F7),0,3)||bitque(inb(0x1F7),0,0)))
{

 flag=1;}
 monitor_write("polling");
 };


  //while(inb(0x1F7)!=8)//||flag++||inb(0x1F7)==1)
  //{
  monitor_write("waiting");

 // }
 // while(inb(0x1F7)!=1)//||flag++||inb(0x1F7)==1)
  //{
 // monitor_write("waiting: for error flag");
 // }
  //if (flag==0)
  //monitor_clear();
  i=0;
  while(i<50){id[i]=inw(0x1F0);

  monitor_put('     ');
  monitor_write_dec(i);
  monitor_put(':');
  monitor_write_hex(id[i]);

  i++;
  }
  monitor_write("done storing words");

}
