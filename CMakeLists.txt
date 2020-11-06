cmake_minimum_required(VERSION 3.16)
project(2_course_cpp)

set(CMAKE_CXX_STANDARD 14)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_link_options(-fsanitize=address -g -Wall -Werror)
endif ()
# add coverage
#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
#    add_link_options(-fprofile-instr-generate)
#    link_libraries(clang_rt.profile-x86_64)
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#    add_compile_options(--coverage)
#    link_libraries(gcov)
#endif ()

add_executable(2_course_cpp 2nd_contest/SmartPointer/main.cpp)