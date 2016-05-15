#!/bin/bash
# diffs should run clean

./run -t 4 -s 0 test/d2/in1.bin test/d2/in2.bin
diff <(sort --parallel=4 out5.txt) <(gunzip -c test/d2/out5.txt.gz | sort --parallel=4)

./run -t 4 -s 0 test/d3/in1.bin test/d3/in2.bin
diff <(sort --parallel=4 out5.txt) <(gunzip -c test/d3/out5.txt.gz | sort --parallel=4)

./run -t 4 -s 0 test/d4/in1.bin test/d4/in2.bin
diff <(sort --parallel=4 out5.txt) <(gunzip -c test/d4/out5.txt.gz | sort --parallel=4)

rm out5.txt
