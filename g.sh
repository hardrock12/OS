rm *.*~
git status
read commit
git add .
git commit -m "$commit"
git log

git push gcode master
