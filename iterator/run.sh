#! /bin/bash
g++ it.cc -g -o it
valgrind --tool=memcheck --leak-check=full ./it
./it