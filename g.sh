rm *.c~
rm *.sh~
rm *.obj~
git status
read commit
git add .
git commit -m "$commit"


git push gcode master
