#!/bin/sh

#valgrind --tool=memcheck ./run -s 0 test/d2/in1.bin test/d2/in2.bin
valgrind --tool=memcheck ./run -n 1000000 -k 10000 -b 0.001 -s 1 test/d2/in1.bin test/d2/in2.bin
