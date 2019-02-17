cmake_minimum_required(VERSION 3.13)
project(ConsoleTrees C)

set(CMAKE_C_STANDARD 99)

add_executable(ConsoleTrees src/example.c src/lib/utils/types.h src/lib/utils/calculators.h src/lib/utils/calculators.c src/lib/utils/helpers.h src/lib/utils/helpers.c src/lib/visualization/helpers.visualization.c src/lib/visualization/helpers.visualization.h src/lib/visualization/logick.visualization.c src/lib/visualization/logick.visualization.h src/lib/ConsoleTrees.h src/lib/tools/tree-methods.c src/lib/tools/tree-methods.h)