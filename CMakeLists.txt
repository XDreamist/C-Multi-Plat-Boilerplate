cmake_minimum_required(VERSION 3.28)

project("C-MULTI-PLAT-BOILERPLATE" VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_NAME "app")
set(MAIN_FILES "src/main.cpp")

option(USE_QT "Use Qt instead of ImGui" OFF)

if(USE_QT)
    find_package(Qt6 REQUIRED Widgets)
        
    add_executable(${EXECUTABLE_NAME} ${MAIN_FILES})

    target_link_libraries(${EXECUTABLE_NAME} Qt6::Widgets)
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${Qt6Widgets_INCLUDE_DIRS})

    target_compile_definitions(${EXECUTABLE_NAME} PRIVATE QT_PRESENT)

else()
    set(IMGUI_DIR "dep/imgui/")
    set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    )

    find_package(OpenGL REQUIRED)
    find_package(glfw3 3.3 REQUIRED)

    add_executable(${EXECUTABLE_NAME} ${MAIN_FILES} ${IMGUI_SOURCES})

    target_link_libraries(${EXECUTABLE_NAME} OpenGL::GL glfw)
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${IMGUI_DIR})
endif()