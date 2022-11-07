cmake_minimum_required(VERSION 3.22)

project(hanabi)

message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

# OS
if (APPLE)
    message(STATUS " Current OS: APPLE")
endif()

# Set compile parameters
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set project version
set (HANABI_VERSION_MAJOR 0)
set (HANABI_VERSION_MINOR 0)

set (EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")


FILE(GLOB SOURCE_FILES src/*.cpp)


configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/sysconfig/SysConfig.h.in
    ${EXECUTABLE_OUTPUT_PATH}/sysconfig/SysConfig.h
)

add_executable(
    hanabi 
    ${SOURCE_FILES}
)

target_include_directories(
    hanabi PUBLIC
    "${EXECUTABLE_OUTPUT_PATH}/sysconfig"
    ${CMAKE_CURRENT_SOURCE_DIR}/deps

    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw-3.3.7/include
)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw-3.3.7)

target_link_libraries(
    hanabi
    glfw
)