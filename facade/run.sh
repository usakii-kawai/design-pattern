#! /bin/bash
g++ fa.cc -g -o fa
valgrind --tool=memcheck --leak-check=full ./fa
./fa