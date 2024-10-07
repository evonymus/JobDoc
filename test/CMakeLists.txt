
#if(BUILD_TESTING)
    add_executable(my_test first_test.cpp)
    target_link_libraries(my_test PRIVATE GTest::gtest_main job_lib)

    include(GoogleTest)
    gtest_discover_tests(my_test)
#endif()