#! /bin/bash
g++ -g sg.cc -o sg
valgrind --tool=memcheck --leak-check=full ./sg
./sg