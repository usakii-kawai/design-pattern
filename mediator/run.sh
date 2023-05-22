#! /bin/bash
g++ md.cc -g -o md
valgrind --tool=memcheck --leak-check=full ./md
./md