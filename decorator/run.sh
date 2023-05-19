#! /bin/bash
g++ dr.cc -g -o dr
valgrind --tool=memcheck --leak-check=full ./dr
./dr