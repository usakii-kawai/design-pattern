#! /bin/bash

g++ -g bg.cc -o bg
valgrind --tool=memcheck --leak-check=full ./bg
./bg