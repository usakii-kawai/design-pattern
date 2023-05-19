#! /bin/bash
g++ px.cc -o px
valgrind --tool=memcheck --leak-check=full ./px
echo "--------------------"
./px