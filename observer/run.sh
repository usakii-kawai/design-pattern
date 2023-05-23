#! /bin/bash
g++ os.cc -o os -g
valgrind --tool=memcheck --leak-check=full ./os
./os