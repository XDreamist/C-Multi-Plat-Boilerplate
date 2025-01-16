cmake_minimum_required(VERSION 3.28)

set(YOUR_PROJECT_NAME "C-MULTI-PLAT-BOILERPLATE")
set(EXECUTABLE_NAME "app")
set(MAIN_FILES "src/main.cpp")

set(IMGUI_DIR "dep/imgui/")
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(INCLUDE_DIRS "${IMGUI_DIR}")

project(${YOUR_PROJECT_NAME} VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(${EXECUTABLE_NAME} ${MAIN_FILES} ${IMGUI_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} OpenGL::GL glfw)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIRS})