function(install_dependency  DEP)

    configure_file(CMakeLists.txt.in ${DEP}-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${DEP}-download )

    if(result)
        message(FATAL_ERROR "CMake step for ${DEP} failed: ${result}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${DEP}-download )

    if(result)
        message(FATAL_ERROR "Build step for ${DEP} failed: ${result}")
    endif()

    # Add ${DEP} directly to our build.
    add_subdirectory(${CMAKE_BINARY_DIR}/${DEP}-src
        ${CMAKE_BINARY_DIR}/${DEP}-build
        EXCLUDE_FROM_ALL)

endfunction()
