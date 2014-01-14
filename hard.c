#include "hard.h"
#include "common.h"
#define sec 0x1F2
#define r_sta   inb(0x1F7)
#define r_err   inb(0x1F1)
void issue_command(u32int port,u32int data)
{
/*

Wait for drive to clear BUSY.
Load required parameters in the Command Block Registers.
Activate the Interrupt Enable (nIEN) bit.
Wait for drive to set DRDY.
Write the command code to the Command Register.

*/




/*


device control register



+-----+----------+----------------------------------------------------------+
| BIT | Mnemonic | Description                                              |
+-----+----------+----------------------------------------------------------+
|  7  | Reserved |                                                          |
|  6  | Reserved |                                                          |
|  5  | Reserved |                                                          |
|  4  | Reserved |                                                          |
|  3  | 1        | Always set.                                              |
|  2  | SRST     | Host Software Reset bit. When this bit is set the drive  |
|     |          | is held reset. If two drives are daisy chained on the    |
|     |          | interface, this bit resets both drives simultaneously.   |
|     |          |                                                          |
|  1  | nIEN     | Drive Interrupt Enable bit. The enable bit for the drive |
|     |          | interrupt to the host. When nIEN is 0 or the drive is    |
|     |          | selected the host interrupt signal INTRQ is enabled      |
|     |          | through a tri state buffer to the host. When nIEN is 1   |
|     |          | or the drive is not selected the host interrupt signal   |
|     |          | INTRQ is in a hig himpedance state regardless of the     |
|     |          | presence or absence of a pending interrupt.              |
|     |          |                                                          |
|  0  | 0        | Always clear.                                            |
+-----+----------+----------------------------------------------------------+

*/

/*


7. I/O Port Functions


+----+------+------+---+---+---+----------------+---------------+
|Addr|-CS1FX|-CS3FX|SA2|SA1|SA0| Read (-IOR)    | Write (-IOW)  |
+----+------+------+---+---+---+----------------+---------------+-----------+
|    |  0   |  0   | X | X | X | ILLEGAL        | ILLEGAL       | <--+      |
|    |  1   |  1   | X | X | X | High Impedance | Not Used      | Control   |
|3FX |  1   |  0   | 0 | X | X | High Impedance | Not Used      | Block     |
|3FX |  1   |  0   | 1 | 0 | X | High Impedance | Not Used      | Registers |
|3F6 |  1   |  0   | 1 | 1 | 0 | Altern Status  | Device Control|    |      |
|3F7 |  1   |  0   | 1 | 1 | 1 | Drive Address  | Not Used      | <--+      |
+----+------+------+---+---+---+----------------+---------------+-----------+
|1F0 |  0   |  1   | 0 | 0 | 0 | Data Port      | Data Port     | <--+      |
|1F1 |  0   |  1   | 0 | 0 | 1 | Error Register | Precomp       |    |      |
|1F2 |  0   |  1   | 0 | 1 | 0 | Sector Count   | Sector Count  | Command   |
|1F3 |  0   |  1   | 0 | 1 | 1 | Sector Number  | Sector Number | Block     |
|1F4 |  0   |  1   | 1 | 0 | 0 | Cylinder Low   | Cylinder Low  | Registers |
|1F5 |  0   |  1   | 1 | 0 | 1 | Cylinder High  | Cylinder High |    |      |
|1F6 |  0   |  1   | 1 | 1 | 0 | Drive / Head   | Drive / Head  |    |      |
|1F7 |  0   |  1   | 1 | 1 | 1 | Status         | Command       | <--+      |
+----+------+------+---+---+---+----------------+---------------+-----------+
At power-up or after reset, the Command Block Registers are initialized to the following values:

REGISTER          VALUE
1F1 Error         : 01
1F2 Sector Count  : 01
1F3 Sector Number : 01
1F4 Cylinder Low  : 00
1F5 Cylinder High : 00
1F6 Drive / Head  : 00
8. Register Descriptions

1F0: Read/Write: DATA PORT REGISTER
All data transferred between the device data buffer and the host passes through this register. Also, the port to which the sector table is transferred during execution of the Format command. Transfers of ECC bytes during the execution of Read/Write Long commands are 8 bit transfers.
1F1: Read: ERROR REGISTER
Contains status information about the last command executed by the drive. The contents of this register are valid only when the error bit (ERR) in the Status Register is set, except at drive power-up or at the completion of the drive's internal diagnostics, when the register contains a status code. When the error bit (ERR) is set, Error Register bits are interpreted as such:

+-----+--------+-------------------------------------------------------------+
| BIT | Mnemon | Description                                                 |
+-----+--------+-------------------------------------------------------------+
|  7  |  BBK   | Bad block mark detected in the requested sector's ID field  |
|  6  |  UNC   | Uncorrectable data error encountered                        |
|  5  |        | Not used                                                    |
|  4  |  IDNF  | Requested sector's ID field not found                       |
|  3  |        | Not used                                                    |
|  2  |  ABRT  | Command aborted due to drive status error or invalid command|
|  1  |  TK0NF | Track 0 not found during execution of Recalibrate command   |
|  0  |  AMNF  | Data address mark not found after correct ID field found    |
+-----+--------+-------------------------------------------------------------+
1F1: Write: WRITE PRECOMPENSATION
The drive ignores the write precompensation value passed by the host.
1F2: Read/Write: SECTOR COUNT REGISTER
Defines the number of sectors of data to be transferred across the host bus, for the subsequent command. If the value in this register is zero, the sector count is 256 sectors. If the command executes successfully, the value in this register at command completion is zero. As each sector is transferred, the Sector Count register is decremented by one to reflect the number of sectors remaining to be transferred. If the command execution is not successful, this register contains the number of sectors that must be transferred to complete the original request.
1F3: Read/Write: SECTOR NUMBER REGISTER
Contains the ID number of the first sector to be accessed by the subsequent command. The sector can be from one to the maximum number of sectors per track. See the command description for additional information about the contents of the Sector Number Register following command completion whether successful or unsuccessful.
1F4: Read/Write: CYLINDER LOW REGISTER
Contains the eight low order bits of the starting cylinder address for any disk access. On multiple sector transfers that cross cylinder boundaries, this register is updated at the end of the command to reflect the current cylinder number. The least significant bits of the cylinder address are loaded into the cylinder low register.
1F5: Read/Write: CYLINDER HIGH REGISTER
Contains the eight high order bits of the starting cylinder address for any disk access. On multiple sector transfers that cross cylinder boundaries, this register is updated at hte end of the command to reflect the current cylinder number. The most significant bits of the cylinder address are loaded into the cylinder high register.
1F6: Read/Write: DRIVE/HEAD REGISTER
Contains the drive ID number and its head number for any disk access. The contents of the Drive/Head Register are defined on execution of the Initialize Drive Parameters command. The bits are defined as follows:

+-----+----------+---------------------------------------------------------+
| BIT | Mnemonic | Description                                             |
+-----+----------+---------------------------------------------------------+
|  7  | Reserved | Always one.                                             |
|  6  | Reserved | Always zero.                                            |
|  5  | Reserved | Always one.                                             |
|  4  | DRV      | 0 to select primary drive, 1 to select secondary drive. |
|  3  | HS3      | MSB of head number.                                     |
|  2  | HS2      |                                                         |
|  1  | HS1      |                                                         |
|  0  | HS0      | LSB of head number.                                     |
+-----+----------+---------------------------------------------------------+
Upon command completion this register is updated to refplect the head number currently selected.
1F7: Read: STATUS REGISTER
Contains information about the status of the drive and controller. The contents of this register are updated at the completion of each command. When the busy bit is set, no other bits in the Command Block Registers are valid. When the busy bit is not set, the information in the Status Register and Command Block Registers is valid.

+-----+----------+----------------------------------------------------------+
| BIT | Mnemonic | Description                                              |
+-----+----------+----------------------------------------------------------+
|  7  |  BUSY    | Busy bit. Set by the controller logic of the drive when  |
|     |          | ever the drive has access to and the host is locked out  |
|     |          | of the Command Block Registers. Set under the following  |
|     |          | conditions:                                              |
|     |          |  o Within 400 nsec after the negation of RESET or after  |
|     |          |    SRST is set in the Device Control Register. After a   |
|     |          |    reset it is recomended that BUSY be set no more than  |
|     |          |    30 seconds.                                           |
|     |          |  o Within 400 nsec of a host write to the Command        |
|     |          |    Register with a Recalibrate, Read Long, Read Buffer,  |
|     |          |    Read, Read Verify, Initialize Drive Parameters, Seek  |
|     |          |    Identify Drive, or Execute Drive Diagnostic command.  |
|     |          |  o Within 5 microseconds following the transfer of 512   |
|     |          |    bytes of data during the execution of a Write, Write  |
|     |          |    Buffer or Format Track command; or 512 bytes of data  |
|     |          |    and the appropriate number of ECC bytes during the    |
|     |          |    execution of a Write Long command.                    |
|     |          |    When BUSY is set no Command Block Register can be     |
|     |          |    written too and a read of any Command Block Register  |
|     |          |    returns the contents of the Status Register.          |
|     |          |                                                          |
|  6  |  DRDY    | Drive Ready bit. Indicates that the drive is ready to    |
|     |          | accept commands. When and error occurs, this bit stays   |
|     |          | unchanged until the host reads the Status Register then  |
|     |          | again indicates that hte drive is ready. On power up,    |
|     |          | this bit should be cleared and should remain cleared     |
|     |          | until the drive is up to speed and ready to accept a     |
|     |          | command.                                                 |
|     |          |                                                          |
|  5  |  DWF     | Drive Write Fault bit. When an error occurs, this bit    |
|     |          | remains unchanged until the host reads the Status        |
|     |          | Register, then again indicates the current write fault   |
|     |          | status.                                                  |
|     |          |                                                          |
|  4  |  DSC     | Drive Seek Complete bit. This bit is set when a seek     |
|     |          | operation is complete and the heads are settled over a   |
|     |          | track. When an error occurs, this bit remains unchanged  |
|     |          | until the host reads the Status Register, then again it  |
|     |          | indicates the current seek complete status.              |
|     |          |                                                          |
|  3  |  DRQ     | Data Request bit. When set it indicates that the drive   |
|     |          | is ready to transfer a word or byte of data between the  |
|     |          | host and the data port.                                  |
|     |          |                                                          |
|  2  |  CORR    | Corrected Data bit. When a correctable data error has    |
|     |          | been encountered and the data has been corrected, this   |
|     |          | bit is set. This condition does not terminate a multi    |
|     |          | sector read operation.                                   |
|     |          |                                                          |
|  1  |  INDEX   | Index bit. Set when the index mark is detected once per  |
|     |          | disk revolution.                                         |
|     |          |                                                          |
|  0  |  ERROR   | Error bit. When set indicates that the previous command  |
|     |          | ended in an error. The other bits in the Error Register  |
|     |          | and Status Register contain additional information about |
|     |          | the cause of the error.                                  |
+-----+----------+----------------------------------------------------------+
1F7: Write: COMMAND REGISTER
When the host request a command it is transferred to the hard drive through an eight bit code written to the command register. As soon as the drive receives a command in its command register, it begins execution of the command. The following table lists the commands in alphabetical order and the parameters for each executable command:

+--------+---------------------------------+-----------------+
| Command| Command Description             | Parameters Used |
| Code   |                                 | PC SC SN CY DH  |
+--------+---------------------------------+-----------------+
| 98h  @ | Check Power Mode                |    V        D   |
| E5h  @ | Check Power Mode (same as 98h)  |    V        D   |
| 90h    | Execute Drive Diagnostic        |             D+  |
| 50h    | Format Track                    |          V  V   |
| ECh  @ | Identify Drive                  |             D   |
| 97h  @ | Idle                            |    V        D   |
| E3h  @ | Idle (same as 97h)              |    V        D   |
| 95h  @ | Idle Immediate                  |             D   |
| E1h  @ | Idle Immadiate (same as 95h)    |             D   |
| 91h    | Initialize Drive Parameters     |    V        V   |
| E4h  @ | Read Buffer                     |             D   |
| C8h  @ | Read DMA With Retry             |  >> Unknown <<  |
| C9h  @ | Read DMA                        |  >> Unknown <<  |
| C4h  @ | Read Multiple                   |    V  V  V  V   |
| 20h    | Read Sectors With Retry         |    V  V  V  V   |
| 21h    | Read Sectors                    |    V  V  V  V   |
| 22h    | Read Long With Retry            |    V  V  V  V   |
| 23h    | Read Long                       |    V  V  V  V   |
| 40h    | Read Verify Sectors With Retry  |    V  V  V  V   |
| 41h    | Read Verify Sectors             |    V  V  V  V   |
| 1Xh    | Recalibrate                     |             D   |
| 7Xh    | Seek                            |          V  V   |
| EFh  @ | Set Features                    |  V          D   |
| C6h  @ | Set Multiple Mode               |    V        D   |
| 99h  @ | Set Sleep Mode                  |             D   |
| E6h  @ | Set Sleep Mode (same as 99h)    |             D   |
| 96h  @ | Standby                         |    V        D   |
| E2h  @ | Standby (same as 96h)           |    V        D   |
| 94h  @ | Standby Immediate               |             D   |
| E0h  @ | Standby Immediate (same as 94h) |             D   |
| 8Xh    | Vendor Unique                   |  >> Unknown <<  |
| 9Ah    | Vendor Unique                   |  >> Unknown <<  |
| C0h    | Vendor Unique                   |  >> Unknown <<  |
| C1h    | Vendor Unique                   |  >> Unknown <<  |
| C2h    | Vendor Unique                   |  >> Unknown <<  |
| C3h    | Vendor Unique                   |  >> Unknown <<  |
| F5h    | Vendor Unique                   |  >> Unknown <<  |
| F6h    | Vendor Unique                   |  >> Unknown <<  |
| F7h    | Vendor Unique                   |  >> Unknown <<  |
| F8h    | Vendor Unique                   |  >> Unknown <<  |
| F9h    | Vendor Unique                   |  >> Unknown <<  |
| FAh    | Vendor Unique                   |  >> Unknown <<  |
| FBh    | Vendor Unique                   |  >> Unknown <<  |
| FCh    | Vendor Unique                   |  >> Unknown <<  |
| FDh    | Vendor Unique                   |  >> Unknown <<  |
| FEh    | Vendor Unique                   |  >> Unknown <<  |
| FFh    | Vendor Unique                   |  >> Unknown <<  |
| E8h  @ | Write Buffer                    |             D   |
| CAh  @ | Write DMA With Retry            |  >> Unknown <<  |
| CBh  @ | Write DMA                       |  >> Unknown <<  |
| C5h  @ | Write Multiple                  |    V  V  V  V   |
| E9h  @ | Write Same                      |  >> Unknown <<  |
| 30h    | Write Sectors With Retry        |    V  V  V  V   |
| 31h    | Write Sectors                   |    V  V  V  V   |
| 32h    | Write Long With Retry           |    V  V  V  V   |
| 33h    | Write Long                      |    V  V  V  V   |
| 3Ch  @ | Write Verify                    |    V  V  V  V   |
+--------+---------------------------------+-----------------+
KEY FOR SYMBOLS IN ABOVE TABLE:

PC    Register 1F1: Write Precompensation
SC    Register 1F2: Sector Count
SN    Register 1F3: Sector Number
CY    Register 1F4+1F5: Cylinder low + high
DH    Register 1F6: Drive / Head

@     These commands are optional and may not be supported by some drives.
D     Only DRIVE parameter is valid, HEAD parameter is ignored.
D+    Both drives execute this command regardless of the DRIVE parameter.
V     Indicates that the register contains a valid paramterer.
Commands with >> Unknown << Parameters are not described in this document.
If a parameter is blank, then the command does not require the contents of that register.

3F6: Read: Alternate Status Register
Contains the same information as the Status Register in the Command Block. Reading the Alternate Status Register does not imply an interrupt acknowledge from the host or clear a pending interrupt. See the description of the Status Register above for a definition of bits in this register.
3F6: Write: Device Control Register
The bits in the Device Control Register are lister in the table below:

+-----+----------+----------------------------------------------------------+
| BIT | Mnemonic | Description                                              |
+-----+----------+----------------------------------------------------------+
|  7  | Reserved |                                                          |
|  6  | Reserved |                                                          |
|  5  | Reserved |                                                          |
|  4  | Reserved |                                                          |
|  3  | 1        | Always set.                                              |
|  2  | SRST     | Host Software Reset bit. When this bit is set the drive  |
|     |          | is held reset. If two drives are daisy chained on the    |
|     |          | interface, this bit resets both drives simultaneously.   |
|     |          |                                                          |
|  1  | nIEN     | Drive Interrupt Enable bit. The enable bit for the drive |
|     |          | interrupt to the host. When nIEN is 0 or the drive is    |
|     |          | selected the host interrupt signal INTRQ is enabled      |
|     |          | through a tri state buffer to the host. When nIEN is 1   |
|     |          | or the drive is not selected the host interrupt signal   |
|     |          | INTRQ is in a hig himpedance state regardless of the     |
|     |          | presence or absence of a pending interrupt.              |
|     |          |                                                          |
|  0  | 0        | Always clear.                                            |
+-----+----------+----------------------------------------------------------+
3F7: Read: Drive Address Register
This port returns the drive select and head select addresses for the drive currently selected. The Drive Address bits are listed in the table below:

+-----+----------+------------------------------------------------------+
| BIT | Mnemonic | Description                                          |
+-----+----------+------------------------------------------------------+
|  7  | HiZ      | This bit is in high impedance when read.             |
|  6  | nWTG     | Write Gate bit. When a write to the hard drive is in |
|     |          | progress, nWTG is 0                                  |
|  5  | nHS3     | Negated MSB of head number                           |
|  4  | nHS2     |                                                      |
|  3  | nHS1     |                                                      |
|  2  | nHS0     | Negated LSB of head number.                          |
|  1  | nDS1     | Drive 1 Select bit. When 0, Drive 1 is selected.     |
|  0  | nDS0     | Drive 0 Select bit. When 0, Drive 0 is selected.     |
+-----+----------+------------------------------------------------------+
9. Command Descriptions

The drive decodes and executes commands loaded into the Command Register. In applications involving two hard drives, both drives receive all commands but only the selected drive executes commands. The recommended procedure for executing a command on the selected drive is:
Wait for drive to clear BUSY.
Load required parameters in the Command Block Registers.
Activate the Interrupt Enable (nIEN) bit.
Wait for drive to set DRDY.
Write the command code to the Command Register.
Execution of the command begins as soon as the drive loads the Command Block Register. The remainder of this section describes the function of each command.
90h: Execute Drive Diagnostic
Performs internal diagnostic tests implemented by the drive. Drive 0 sets BUSY within 400 nsec of the receipt of the command.
If Drive 1 is present:

Both drives execute diagnostics.
Drive 0 waits up to 5 seconds for Drive 1 to assert PDIAG-
If Drive 1 does not assert PDIAG-, indicatinf a failure, Drive 0 appends 80h with its own diagnostic status.
If the host detects a Drive 1 diagnostic failure when reading Drive 0 status it sets the DRV bit then reads the Drive 1 status.
If Drive 1 is not present:
Drive 0 reports only its own diagnostic results.
Drive 0 clears BUSY and generates an interrupt.
If Drive 1 fails diagnostics, Drive 0 appends 80h with its own diagnostic status and loads that code in the Error Register. If Drive 1 passes its diagnostics or no Drive 1 is present, Drive 0 appends 00h with its own diagnostic status and loads that in the Error Register.
The Diagnostic Code written to the Error Register is a unique 8 bit code as listed below.


+------+----------------------------------+
| Code | Description                      |
+------+----------------------------------+
|  01  | No error detected.               |
|  02  | Formatter device error.          |
|  03  | Sector buffer error.             |
|  04  | ECC circuitry error.             |
|  05  | Controller microprocessor error. |
|  8X  | Drive 1 failed.                  |
+------+----------------------------------+
*/
while(bitque(r_sta,0,7)){};



}
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
  outb(0x3F6,0x12);
  outb(0x1F2,0xEC);
  int flag=0 ;



  monitor_write_hex(inb(0x1F7));

i=0;
while(i<256)
{
   id[i]=inw(0x1F0);

   monitor_write_hex(id[i]);
   i++;
}
}
