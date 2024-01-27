project(SimpleNormalMapper)

cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.10)

# Global game version
set(VERSION_MAJOR "1")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

message("\n${CMAKE_PROJECT_NAME} ${VERSION}\n")
message(STATUS "System name       : ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "System version    : ${CMAKE_SYSTEM_VERSION}")
message(STATUS "Compiler identity : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler version  : ${CMAKE_CXX_COMPILER_VERSION}")

# Some common CPack variables
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})

set(CPACK_PACKAGE_NAME snm)
set(CPACK_PACKAGE_VENDOR Juzzlin)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Quickly and easily generate normal maps from your 2D images")
set(CPACK_PACKAGE_ICON ${CMAKE_SOURCE_DIR}/data/icons/snm.png)

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/COPYING)
set(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/README.md)

# Default to release C++ flags if CMAKE_BUILD_TYPE not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel." FORCE)
endif()

if(UNIX)
    include("InstallLinux.cmake")
elseif(WIN32)
    include("InstallWindows.cmake")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR MINGW OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

    # CMAKE_CXX_STANDARD supported only by versions >= 3.1
    if (CMAKE_VERSION VERSION_LESS "3.1")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()

    # Automatically use ccache if found
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif(CCACHE_FOUND)

elseif(MSVC)
    add_definitions(-DNOMINMAX)
endif()

set(BINARY_NAME "snm")

add_definitions(-DVERSION="${VERSION}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_MIN_VER 5.9.5) # The version in Ubuntu 18.04 LTS
if (BUILD_WITH_QT6)
    find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)
else()
    find_package(QT NAMES Qt5 COMPONENTS Core REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)
endif()
message(STATUS "Qt version found  : ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}\n")

# Install paths depend on the build type and target platform
setup_install_targets()

add_subdirectory(src)

