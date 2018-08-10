cmake_minimum_required(VERSION 2.8.2)

# project(googletest-download NONE)

include(ExternalProject)

ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/googletest-src"
  BINARY_DIR        "${CMAKE_BINARY_DIR}/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(dionysus
  GIT_REPOSITORY    https://github.com/mrzv/dionysus
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/dionysus-src"
  BINARY_DIR        "${CMAKE_BINARY_DIR}/dionysus-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
