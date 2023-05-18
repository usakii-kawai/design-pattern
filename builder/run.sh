#! /bin/bash
g++ -g bd.cc -o bd
valgrind --tool=memcheck --leak-check=full ./bd
./bd