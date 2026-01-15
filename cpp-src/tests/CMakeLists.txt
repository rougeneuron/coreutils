include(GoogleTest)

add_executable(true_test true_test.cpp)
target_link_libraries(true_test GTest::gtest_main)

gtest_discover_tests(true_test)
