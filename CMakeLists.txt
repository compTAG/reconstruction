cmake_minimum_required(VERSION 2.8.2)

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


# setup dionysus
install_dependency("dionysus")

# setup testing
enable_testing()

install_dependency("googletest")


# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(example example.cpp)
target_link_libraries(example gtest_main)
add_test(NAME example_test COMMAND example)



find_package(Boost)

set(DIONYSUS_INCLUDE_DIR "${CMAKE_BINARY_DIR}/dionysus-src/include")
set(RECONSTRUCTION_INCLUDE_DIR "./include")

include_directories(
    ${DIONYSUS_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR}
    ${RECONSTRUCTION_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(height-filtration  filtration-persistence.cpp)
target_link_libraries(height-filtration ${libraries})
