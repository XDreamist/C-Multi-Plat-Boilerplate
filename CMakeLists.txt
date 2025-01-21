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

# Qt-specific configuration
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt packages
set(QT_DIR "" CACHE PATH "Path to Qt installation directory")
if((QT_DIR AND EXISTS "${QT_DIR}") OR NOT WIN32)
    set(CMAKE_PREFIX_PATH ${QT_DIR})
    find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
    # Add Qt includes and libraries
    list(APPEND LIB_NAMES Qt6::Widgets Qt6::Core)
    message(STATUS "Using Qt6 for GUI")
else()
    message(WARNING "QT_DIR is not set or is invalid. Please set QT_DIR to the path of your Qt installation.")
endif()

# Add executable
add_executable(${EXECUTABLE_NAME} ${SRC_FILES} ${EXTERNAL_SOURCES})

# Add include directories
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIB_NAMES})

# If the config didn't run the windeployqt.exe automatically
if(WIN32 AND EXISTS "${WINDEPLOYQT_EXECUTABLE}")
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}" $<TARGET_FILE:${EXECUTABLE_NAME}>
        COMMENT "Running windeployqt to deploy Qt dependencies"
    )
else()
    message(WARNING "windeployqt executable not found. Ensure QT_DIR is set correctly.")
endif()

if(ANDROID)
    # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
    # If you are developing for iOS or macOS you should consider setting an
    # explicit, fixed bundle identifier manually though.
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTest
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )
    include(GNUInstallDirs)
    install(TARGETS ${EXECUTABLE_NAME}
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()