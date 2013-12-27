clear
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "
echo  "                                         "





echo "Buiding ASSwmbly"
nasm -felf -o start.o start.asm
nasm -felf -o interrupt.o interrupt.asm
nasm -felf -o gdt.o gdt.asm
echo "bmain"
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c
echo "btimer"
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o timer.o timer.c
echo "bcommon"
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o common.o common.c
echo "bdesc_tables"
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o descriptor_tables.o descriptor_tables.c
echo "bmonitor"
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o monitor.o monitor.c
echo "bisr"
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o isr.o isr.c
echo "linking........."
ld -T link.ld -o ./iso/boot/kernel.bin start.o main.o monitor.o common.o descriptor_tables.o timer.o isr.o interrupt.o gdt.o
rm *.o

		