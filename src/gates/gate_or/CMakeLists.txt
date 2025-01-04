
add_library(gate_or gate_or.cpp)
target_include_directories(gate_or PUBLIC .)

add_executable(test_or main.cpp)

target_link_libraries(test_or gate_or)