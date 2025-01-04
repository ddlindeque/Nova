
add_library(gate_nand gate_nand.cpp)
target_include_directories(gate_nand PUBLIC .)

add_executable(test_nand main.cpp)

target_link_libraries(test_nand gate_nand)