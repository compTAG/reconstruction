cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(install_dependency)

enable_testing()

find_package(Boost)

install_dependency("dionysus")
set(DIONYSUS_INCLUDE_DIR "${CMAKE_BINARY_DIR}/dionysus-src/include")

install_dependency("googletest")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # fix settings on Windows

# setup the includes
set(RECONSTRUCTION_INCLUDE_DIR "./include")
include_directories(
    ${DIONYSUS_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR}
    ${RECONSTRUCTION_INCLUDE_DIR})

# setup the build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# build the test
add_executable(example example.cpp)
target_link_libraries(example gtest_main)
add_test(NAME example_test COMMAND example)

# build the executable
add_executable(height-filtration  filtration-persistence.cpp)
target_link_libraries(height-filtration ${libraries})
