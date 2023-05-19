#! /bin/bash
g++ fw.cc -o fw
valgrind --tool=memcheck --leak-check=full ./fw
./fw