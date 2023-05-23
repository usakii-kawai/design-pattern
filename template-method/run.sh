#! /bin/bash
g++ -g tm.cc -o tm
valgrind --tool=memcheck --leak-check=full ./tm
./tm