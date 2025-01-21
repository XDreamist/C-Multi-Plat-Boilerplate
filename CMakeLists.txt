cmake_minimum_required(VERSION 3.16)

project(C-MULTI-PLAT-BOILERPLATE VERSION 1.0 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)
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

# Other sources to build
set(EXTERNAL_SOURCES "")

# Libraries to link
set(LIB_NAMES "")

# ImGui configuration
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/dep/imgui")
# Add ImGui sources
list(APPEND EXTERNAL_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
# Find OpenGL and GLFW
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
# Add includes and libraries
include_directories(${IMGUI_DIR})
list(APPEND LIB_NAMES OpenGL::GL glfw)
message(STATUS "Using ImGui for GUI")

# Add executable
add_executable(${EXECUTABLE_NAME} ${SRC_FILES} ${EXTERNAL_SOURCES})

# Add include directories
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIB_NAMES})
