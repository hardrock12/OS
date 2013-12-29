echo "Actually Creating bootable ISO and Running thereby in Virtual box"
echo"========================================================================================="


grub-mkrescue -o myos.iso iso
vboxmanage startvm unknown


