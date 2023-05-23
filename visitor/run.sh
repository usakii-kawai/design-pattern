#! /bin/bash
g++ -g vt.cc -o vt
valgrind --tool=memcheck --leak-check=full ./vt
./vt