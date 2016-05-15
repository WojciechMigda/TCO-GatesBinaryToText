################################################################################
project( "TCO-GatesBinaryToText" C )

cmake_minimum_required( VERSION 2.8.3 )

set( CMAKE_ECLIPSE_VERSION 3.8 )
set( _ECLIPSE_VERSION 3.8 )

add_definitions( -D_GNU_SOURCE -std=c99 )

#add_definitions( -O0 -ggdb -Wall -pedantic -mmmx -msse -msse2 -msse3 -s -pipe -Wno-sign-compare -march=native )
#add_definitions( -O2 -ggdb -std=c++11 -Wall -pedantic -mmmx -msse -msse2 -msse3 -s -pipe -Wno-sign-compare -march=native )
#add_definitions( -O2 -g -unroll-loops -std=c++11 -Wall -pedantic -mmmx -msse -msse2 -msse3 -s -pipe -Wno-sign-compare -march=native )
add_definitions( -O3 -DNDEBUG -g -unroll-loops -Wall -pedantic -mmmx -msse -msse2 -msse3 -s -pipe -Wno-sign-compare -march=native )
#add_definitions( -O3 -DNDEBUG )



################################################################################

include_directories(
    src
)

################################################################################

add_executable( run
    src/deque.c
    src/io.c
    src/main.c
    src/num_procs.c
    src/out_sorted.c
    src/out3.c
    src/out4.c
    src/out5.c
    src/parse_program_options.c
    src/read_data_context.c
    src/read_scored_index.c
    src/read_tuples_and_scored_index.c
    src/read_scored_tuples.c
    src/read_sorted_index.c
    src/sort_indexed_scores.c
    src/timestamp.c
    src/work.c
)

target_link_libraries( run "m" "pthread" )

add_executable( utoa_test src/utoa_test.c )

add_executable( deque_test src/deque_test.c src/deque.c )

add_executable( cstring_score_test src/cstring_score_test.c )

add_executable( naive_utoa_test src/naive_utoa_test.c )

################################################################################
