
cmake_minimum_required(VERSION 3.16)

project(soc-interconnect-memory-subsystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SystemCLanguage CONFIG REQUIRED
    PATHS "C:/SystemC/install/lib/cmake/SystemCLanguage"
    NO_DEFAULT_PATH
)

add_executable(soc-interconnect-memory-subsystem
    src/sc_main.cpp
    src/cpu_initiator.cpp
    src/memory_target.cpp
    tests/tests_read_write.cpp
)

target_include_directories(soc-interconnect-memory-subsystem
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(soc-interconnect-memory-subsystem
    PRIVATE SystemC::systemc
)
