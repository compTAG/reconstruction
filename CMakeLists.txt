cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
include(install_dependency)

# set the build type.  Good values are debug or release
set(CMAKE_BUILD_TYPE debug)

# setup dependencies
find_package(Boost)

install_dependency("dionysus")
set(DIONYSUS_INCLUDE_DIR "${CMAKE_BINARY_DIR}/dionysus-src/include")

set(PLF_NANOTIMER_DIR "${CMAKE_BINARY_DIR}/plf_nanotimer-src")

enable_testing()
install_dependency("googletest")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # fix settings on Windows

# setup the build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

# setup the includes
set(RECONSTRUCTION_INCLUDE_DIR "./include")
include_directories(
    ${DIONYSUS_INCLUDE_DIR}
    ${PLF_NANOTIMER_DIR}
    ${Boost_INCLUDE_DIR}
    ${RECONSTRUCTION_INCLUDE_DIR}
)

# setup remainder of project
add_subdirectory(test)
add_subdirectory(example)
add_subdirectory(bindings/python)
