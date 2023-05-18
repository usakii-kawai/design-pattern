#! /bin/bash
g++ sg.cc -o sg && ./sg > sumLine.txt
count=$(wc -l sumLine.txt | sed 's/[^0-9]//g')
count=$(expr $count - 1)
echo  $count