cmake_minimum_required(VERSION 3.10)

project(cpy)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(cpy copy_osc52.c)

enable_testing()
function(add_case test_name)
    add_test(NAME ${test_name}
             COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_name}.sh)
    set_tests_properties(${test_name} PROPERTIES ENVIRONMENT "CMD=$<TARGET_FILE:cpy>")
endfunction()

add_case("01_case_single_line")
add_case("02_case_lorem")
add_case("03_case_lorem_many_terminating_newlines")
