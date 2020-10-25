cmake_minimum_required(VERSION 3.17)
project(2_course_cpp)

set(CMAKE_CXX_STANDARD 14)

# add coverage
#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
#    add_link_options(-fprofile-instr-generate)
#    link_libraries(clang_rt.profile-x86_64)
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#    add_compile_options(--coverage)
#    link_libraries(gcov)
#endif ()

add_executable(2_course_cpp "1 contest/BufferedReader/main.cpp" "1 contest/BufferedReader/buffered_reader.h")