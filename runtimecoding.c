#include "runtimecoding.h"
#include "common.h"
#define version 2



u32int encode(u32int source,u32int sz)
{
//first layer
monitor_write("Version:");
monitor_write_dec(version);
monitor_put('\n');
u32int i=0;
u32int temp=0x1;
u32int result=0;                                 // detect run by symbol 00
u8int marker=0x0;
u8int layer1[32];
while(i<32)
{monitor_write_dec((source>>i)&0X3);

i++;}
i=0;
while(i<32)
{layer1[i]=0;//  clearing garbage value
i++;
};

i=0;

while(i<32)
{
if(((source>>i)&0X3)==temp)
{
monitor_write("X:");
//monitor_put('\n');
monitor_write_dec(marker);
layer1[marker]=layer1[marker]+1;
monitor_write_dec(layer1[marker]);

//monitor_put('\n');
s("  ");
i++;
}

else{
temp+=1;
temp%=4;


marker++;
}


}

i=0;
while(i<=marker)
{monitor_write_dec(layer1[i]);
s(" ");
if(layer1[i]>9)
{
  result*=100;
}
else{
result*=10;
}
result+=layer1[i];

i++;

}
s("\n");

//u32int result;
return result ;

}
