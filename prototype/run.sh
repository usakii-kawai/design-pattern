#! /bin/bash
g++ pt.cc -g -o pt
valgrind --tool=memcheck --leak-check=full ./pt
./pt