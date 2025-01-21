cmake_minimum_required(VERSION 3.16)

project(C-MULTI-PLAT-BOILERPLATE VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executable name
set(EXECUTABLE_NAME "EXECUTABLE")

# Source and include directories
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# Glob sources
file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.cpp"
)

# Option to use Qt
option(USE_QT "Use Qt for GUI" ON)
option(USE_IMGUI "Use ImGui for GUI" OFF)

# Other sources to build
set(EXTERNAL_SOURCES "")

# Libraries to link
set(LIB_NAMES "")

# Add executable
add_executable(${EXECUTABLE_NAME} ${SRC_FILES} ${EXTERNAL_SOURCES})

# Add include directories
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIB_NAMES})
