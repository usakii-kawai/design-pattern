#! /bin/bash
g++ cp.cc -o cp
valgrind --tool=memcheck --leak-check=full ./cp
./cp