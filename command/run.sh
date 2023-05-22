#! /bin/bash
g++ -g cmd.cc -o cmd
valgrind --tool=memcheck --leak-check=full ./cmd
./cmd