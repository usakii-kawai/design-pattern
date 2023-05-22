#! /bin/bash
g++ -g cor.cc -o cor
valgrind --tool=memcheck --leak-check=full ./cor
./cor