DEPLOYMENT:

1. make-based:
Execute make in the folder where Makefile.TCO is located, e.g.
make -f Makefile.TCO

2. cmake-based
Execute cmake in the folder where CMakeLists.txt is located, followed by make, e.g.
cmake . && make

Either method shall produce executable named run in the current folder.

When cmake is used it builds few testing executables in additions to the run executable:
  naive_utoa_test - tests correctness of uint32 to ascii conversion
  cstring_score_test - tests correctness of double precision floating value [-1,1] to ascii conversion
  deque_test - tests "deque", or maybe rather single-linked list used to keep value-to-sorted-tuple-index associations

THREADING:

Created executable uses threads. It accepts -t option to pass number of threads to use. This limit, however,
is used only during data loading and sorting stage. Subsequently, it will use 4 or 5 threads, the latter when
the -s option is passed. By default, when -t is absent, number of threads will equal number of CPUs.
