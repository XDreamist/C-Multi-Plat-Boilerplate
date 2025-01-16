cmake_minimum_required(VERSION 3.28)

set(YOUR_PROJECT_NAME "C-MULTI-PLAT-BOILERPLATE")
set(EXECUTABLE_NAME "app")
set(MAIN_FILES "src/main.cpp")

project(${YOUR_PROJECT_NAME} VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${EXECUTABLE_NAME} ${MAIN_FILES})

target_link_libraries(${EXECUTABLE_NAME} OpenGL glfw3)