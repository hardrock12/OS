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
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c
echo "btimer"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o timer.o timer.c
echo "bcommon"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o common.o common.c
echo "bdesc_tables"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o descriptor_tables.o descriptor_tables.c
echo "bmonitor"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o monitor.o monitor.c
echo "bmouse"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o mouse.o mouse.c
echo "bisr"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o isr.o isr.c
echo "bkey"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o key.o key.c
echo "bpaging"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o paging.o paging.c
echo "bkheap"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o kheap.o kheap.c
echo "borderedarray"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o ordered_array.o ordered_array.c
echo "borderedarray"
echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o hard.o hard.c

echo "=================================================================================================================="
gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -fno-builtin -I./include -c -o runc.o runtimecoding.c
echo "linking........."
echo "=================================================================================================================="
ld -T link.ld  -o ./iso/boot/kernel.bin start.o main.o monitor.o common.o descriptor_tables.o timer.o isr.o interrupt.o gdt.o mouse.o key.o paging.o hard.o kheap.o ordered_array.o runc.o
ld -T link.ld  -o kernel.bin start.o  main.o monitor.o common.o descriptor_tables.o timer.o isr.o interrupt.o gdt.o mouse.o key.o paging.o kheap.o ordered_array.o hard.o runc.o
echo  "Running"
qemu --kernel kernel.bin
rm *.o

		
