# **** Instal targets for Windows ****
function(setup_install_targets)

    message(STATUS "Windows build.")

    set(BIN_PATH .)
    set(DOC_PATH .)

    # Add target to copy files to the binary dir.
    add_custom_target(docs ALL
        COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/COPYING ${CMAKE_BINARY_DIR}/COPYING
        COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/README.md ${CMAKE_BINARY_DIR}/README.md
        DEPENDS ${BINARY_NAME})

    install(PROGRAMS ${CMAKE_BINARY_DIR}/${BINARY_NAME}.exe DESTINATION ${BIN_PATH})
    install(FILES COPYING README.md DESTINATION ${DOC_PATH})

endfunction()

