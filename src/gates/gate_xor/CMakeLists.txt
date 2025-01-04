
add_library(gate_xor gate_xor.cpp)
target_link_libraries(gate_xor gate_nand)
target_include_directories(gate_xor PUBLIC .)

add_executable(test_xor main.cpp)

target_link_libraries(test_xor gate_xor)