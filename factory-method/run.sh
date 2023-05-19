#! /bin/bash
g++ fm.cc -o fm
valgrind --tool=memcheck --leak-check=full ./fm
./fm