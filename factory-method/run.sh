#! /bin/bash
g++ fm.cc -o fmcc
valgrind --tool=memcheck --leak-check=full ./fmcc