#! /bin/bash
g++ -g af.cc -o af
valgrind --tool=memcheck --leak-check=full ./af
./af