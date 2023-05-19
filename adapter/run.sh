#! /bin/bash
g++ -g ap.cc -o ap
valgrind --tool=memcheck --leak-check=full ./ap
./ap