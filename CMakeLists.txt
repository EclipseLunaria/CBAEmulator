cmake_minimum_required(VERSION 3.28)
project(cba_emulator C)

add_subdirectory(lib/arm_core)
add_subdirectory(lib/disasm)

include_directories(include)

add_executable(emulator_main
    src/main.c

    )

target_include_directories(emulator_main PRIVATE 
    lib/disasm/include 
    lib/arm_core/include
    )
target_link_libraries(emulator_main PRIVATE arm_core disasm)
