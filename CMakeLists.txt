cmake_minimum_required(VERSION 3.28)

project("C-MULTI-PLAT-BOILERPLATE" VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure build types
set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "" FORCE)

# Executable name
set(EXECUTABLE_NAME "EXECUTABLE")

# Source and include directories
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

# Glob sources
file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

# Option to use Qt
option(USE_QT "Use Qt for GUI" OFF)
option(USE_IMGUI "Use ImGui for GUI" OFF)

# Other sources to build
set(EXTERNAL_SOURCES "")

# Libraries to link
set(LIB_NAMES "")

if(USE_QT)
    # Qt-specific configuration
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)

    # Find Qt packages
    set(QT_DIR "" CACHE PATH "Path to Qt installation directory")

    if((QT_DIR AND EXISTS "${QT_DIR}") OR UNIX)
        set(CMAKE_PREFIX_PATH ${QT_DIR})
        find_package(Qt6Widgets REQUIRED)
        find_package(Qt6Core REQUIRED)

        # Add Qt includes and libraries
        list(APPEND LIB_NAMES Qt6::Widgets)
        message(STATUS "Using Qt6 for GUI")
    else()
        message(WARNING "QT_DIR is not set or is invalid. Please set QT_DIR to the path of your Qt installation.")
    endif()
elseif(USE_IMGUI)
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
endif()

# Add executable
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${EXTERNAL_SOURCES})

# Add include directories
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIB_NAMES})

# Add Qt-specific definitions if enabled
if(USE_QT)
    target_compile_definitions(${EXECUTABLE_NAME} PRIVATE QT_PRESENT)

    if(WIN32 AND EXISTS "${WINDEPLOYQT_EXECUTABLE}")
        add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" $<TARGET_FILE:${EXECUTABLE_NAME}>
            COMMENT "Running windeployqt to deploy Qt dependencies"
        )
    elseif(WIN32)
        message(WARNING "windeployqt executable not found. Ensure QT_DIR is set correctly.")
    endif()
endif()
