
add_library(gate_not gate_not.cpp)
target_link_libraries(gate_not gate_nand)
target_include_directories(gate_not PUBLIC .)

add_executable(test_not main.cpp)

target_link_libraries(test_not gate_not)