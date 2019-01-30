cmake_minimum_required(VERSION 2.8.11)

include(ExternalProject)

ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           9318a18
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/googletest-src"
  BINARY_DIR        "${CMAKE_BINARY_DIR}/googletest-build"
  UPDATE_COMMAND    ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(dionysus
  GIT_REPOSITORY    https://github.com/mrzv/dionysus
  GIT_TAG           94fd5a4
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/dionysus-src"
  BINARY_DIR        "${CMAKE_BINARY_DIR}/dionysus-build"
  UPDATE_COMMAND    ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(plf_nanotimer
  GIT_REPOSITORY    https://github.com/mattreecebentley/plf_nanotimer
  GIT_TAG           8c42255
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/plf_nanotimer-src"
  BINARY_DIR        ""
  BINARY_DIR        ""
  UPDATE_COMMAND    ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
