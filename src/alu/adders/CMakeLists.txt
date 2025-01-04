
add_library(half_adder half_adder.cpp full_adder.cpp adder_16bit.cpp)
target_link_libraries(half_adder gate_xor gate_and gate_or types)
target_include_directories(half_adder PUBLIC .)

add_executable(test_adders main.cpp)

target_link_libraries(test_adders half_adder)