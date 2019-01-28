add_subdirectory(backward/backward-cpp)

list(APPEND CMAKE_MODULE_PATH backward/backward-cpp)
find_package(Backward)

add_executable(run_tests run_tests.cpp ${BACKWARD_ENABLE})
target_link_libraries(run_tests gtest_main)
add_test(NAME run_test COMMAND run_tests)


# This will add libraries, definitions and include directories needed by backward
# through an IMPORTED target.
#target_link_libraries(run_tests PUBLIC Backward::Backward)


add_backward(run_tests)


