# Set sources
set(SRC
    about_dlg.cpp
    config.cpp
    control_tool_bar.cpp
    editor.cpp
    editor_view.cpp
    main.cpp
    main_window.cpp
    renderer.cpp
    render_preview.cpp
    settings.cpp
)

set(RCS
    ${CMAKE_SOURCE_DIR}/data/icons/Icons.qrc
)

if(${QT_VERSION_MAJOR} STREQUAL "6")
    qt_add_resources(RC_SRC ${RCS})
# This is needed for Qt < 5.15
else()
    qt5_add_resources(RC_SRC ${RCS})
endif()

# Resource compilation for MinGW
if(MINGW)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/windowsrc.o
        COMMAND
            ${CMAKE_RC_COMPILER}
            -I${CMAKE_SOURCE_DIR} -i${CMAKE_SOURCE_DIR}/data/icons/Windows.rc
            -o ${CMAKE_CURRENT_BINARY_DIR}/windowsrc.o)
    set(SRC ${SRC} ${CMAKE_CURRENT_BINARY_DIR}/windowsrc.o)
endif()

# Add the executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_executable(${BINARY_NAME} WIN32 ${SRC} ${MOC_SRC} ${RC_SRC})

target_link_libraries(${BINARY_NAME} Qt${QT_VERSION_MAJOR}::Widgets)

