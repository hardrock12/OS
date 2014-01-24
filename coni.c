#include "common.h"


int x=0,iflag=0;


u32int getint(int sd)
{if(sd!=-1){
x*=10;x+=(sd-2);
}
else{iflag=1;

}





}
u32int getstored()
{
if(iflag==1)
{return x;}
else
{return -1;}

}
