# CMake entry point
cmake_minimum_required(VERSION 3.22)
message(STATUS "cmake: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")

# PROJECT_SOURCE_DIR       ---
# PROJECT_BINARY_DIR       --- cmake compile path
# CMAKE_CURRENT_SOURCE_DIR --- current CMakeLists.txt path
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# project
project(hanabi)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/publish)

# output cmake paths：
message(STATUS "[__INFO__] CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "[__INFO__] PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "[__INFO__] CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# ---------------------------------------------------#
# src
# ---------------------------------------------------#
FILE(GLOB_RECURSE PIXEL_FILES
    src/engine/*.cpp
    src/sandbox/*.cpp
    src/scripts/*.cpp
)

add_executable(
    hanabi
    ${PIXEL_FILES}
)

target_precompile_headers(hanabi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch/pch.h) # PCH

# macro function to get all .h/.hpp under engine/
MACRO(collect_head_dirs return_list)
    FILE(GLOB_RECURSE new_list

        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sandbox/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sandbox/*.hpp
    )
    SET(dir_list "")

    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()

    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

collect_head_dirs(engine_header_dirs)

list(LENGTH engine_header_dirs engine_header_dirs_count)
message(STATUS "[INFO] Found ${engine_header_dirs_count} engine header directories.")

target_include_directories(hanabi PUBLIC
    ${engine_header_dirs}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scripts
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pch
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sandbox
)

# Link include libraries
target_include_directories(hanabi PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/spdlog-1.x/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw-3.3.9/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb_image
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/spdlog-1.x)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw-3.3.9)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/glad)

target_link_libraries(hanabi
    spdlog
    glfw
    glad
    ${GLFW_STATIC_LIBRARIES}
    ${GLFW_LIBRARIES}
)

# After macOS 10.14 - Some OpenGL API deprecated.
# (Define GL_SILENCE_DEPRECATION to silence these warnings)
target_compile_definitions(hanabi PRIVATE GL_SILENCE_DEPRECATION=1)

# Have to add this to avoid compile error
find_package(OpenGL REQUIRED)
target_link_libraries(hanabi OpenGL::GL)

# IMGUI
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui")

add_library(imgui
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp)

target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_link_libraries(imgui PUBLIC glfw glad OpenGL::GL)
target_include_directories(hanabi PUBLIC ${IMGUI_DIR})
target_link_libraries(hanabi imgui)
