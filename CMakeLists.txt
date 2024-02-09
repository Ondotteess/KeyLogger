cmake_minimum_required(VERSION 3.0.0)
project(KeyLogger VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(PROCESS_LIB process/process.cpp)
set(KEYBOARD_LIB keyboard/keyboard.cpp)

add_library(process STATIC ${PROCESS_LIB})
add_library(keyboard STATIC ${KEYBOARD_LIB})

add_executable(KeyLogger main.cpp)

target_link_libraries(KeyLogger process keyboard)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
