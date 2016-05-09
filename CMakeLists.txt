################################################################################
project( "TCO-GatesBinaryToText" C )

cmake_minimum_required( VERSION 2.8.3 )

set( CMAKE_ECLIPSE_VERSION 3.8 )
set( _ECLIPSE_VERSION 3.8 )


add_definitions( -O0 -ggdb -Wall -pedantic -mmmx -msse -msse2 -msse3 -s -pipe -Wno-sign-compare -march=native )
#add_definitions( -O2 -ggdb -std=c++11 -Wall -pedantic -mmmx -msse -msse2 -msse3 -s -pipe -Wno-sign-compare -march=native )
#add_definitions( -O2 -g -unroll-loops -std=c++11 -Wall -pedantic -mmmx -msse -msse2 -msse3 -s -pipe -Wno-sign-compare -march=native )
#add_definitions( -O3 -DNDEBUG -g -unroll-loops -Wall -pedantic -mmmx -msse -msse2 -msse3 -s -pipe -Wno-sign-compare -march=native )


################################################################################

include_directories(
    src
)

################################################################################

add_executable( run
    src/io.c
    src/main.c
    src/parse_program_options.c
    src/read_scored_tuples.c
    src/run.c
    src/work.c
)

target_link_libraries( run "m" )

################################################################################
