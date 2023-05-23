#! /bin/bash
g++ st.cc -g -o st
valgrind --tool=memcheck --leak-check=full ./st
./st