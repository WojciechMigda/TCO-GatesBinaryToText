#!/bin/bash

./run -n 10000000 -t 4 test/d2/in1.bin test/d2/in2.bin
diff <(sort --parallel=4 out1.txt) <(gunzip -c test/d2/out1.txt.gz | sort --parallel=4)
diff <(sort --parallel=4 out2.txt) <(gunzip -c test/d2/out2.txt.gz | sort --parallel=4)

./run -n 10000000 -t 4 test/d3/in1.bin test/d3/in2.bin
diff <(sort --parallel=4 out1.txt) <(gunzip -c test/d3/out1.txt.gz | sort --parallel=4)
diff <(sort --parallel=4 out2.txt) <(gunzip -c test/d3/out2.txt.gz | sort --parallel=4)

./run -n 10000000 -t 4 test/d4/in1.bin test/d4/in2.bin
diff <(sort --parallel=4 out1.txt) <(gunzip -c test/d4/out1.txt.gz | sort --parallel=4)
diff <(sort --parallel=4 out2.txt) <(gunzip -c test/d4/out2.txt.gz | sort --parallel=4)

#rm out5.txt
