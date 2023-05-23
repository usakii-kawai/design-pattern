#! /bin/bash
g++ mm.cc -g -o mm
valgrind --tool=memcheck --leak-check=full ./mm
./mm