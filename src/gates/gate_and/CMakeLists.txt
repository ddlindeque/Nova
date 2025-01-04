
add_library(gate_and gate_and.cpp)
target_include_directories(gate_and PUBLIC .)

add_executable(test_and main.cpp)

target_link_libraries(test_and gate_and)