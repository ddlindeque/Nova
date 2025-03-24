add_library(hardware
            and_gate.cpp
            nand_gate.cpp
            or_gate.cpp
            nor_gate.cpp
            xor_gate.cpp
            nxor_gate.cpp
            not_gate.cpp
            half_adder.cpp
            full_adder.cpp
            device.cpp)

add_executable(test_gates.exe
               test_gates.cpp)

target_link_libraries(test_gates.exe
                      hardware)

add_executable(test_adders.exe
               test_adders.cpp)

target_link_libraries(test_adders.exe
                      hardware)
