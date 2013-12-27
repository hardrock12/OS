rm *.c~
rm *.sh~
rm *.obj~
git status
read commit
git add .
git commit -m "$commit"
git log --oneline

git push gcode master
