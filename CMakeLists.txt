cmake_minimum_required(VERSION 3.10)

project(test-create-process)

add_executable(caller caller.c)
add_executable(callee1 callee1.c)
add_executable(callee2 callee2.c)

target_link_libraries(caller shlwapi)