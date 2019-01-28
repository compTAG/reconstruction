add_executable(run_tests run_tests.cpp)
target_link_libraries(run_tests gtest_main)
add_test(NAME run_test COMMAND run_tests)
