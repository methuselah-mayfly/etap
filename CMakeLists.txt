# cmake file for the TAP framework (https://testanything.org)
# this is a library that you build unit tests against.  the tests
# built with this library can then be run by a tap test runner.
# there is a tap test runner for POSIX and also for running embedded
# unit tests on the real target (these report their results through
# the arm SWO port)

#############################################
# Create target and set properties
add_library(etap INTERFACE)

# this is an INTERFACE ONLY target, i.e. header only library
target_include_directories(etap INTERFACE include)

#############################################
# And now test the test library!  Only do this on desktop build
# as we have no cross compiled target set up in this demo.
if (NOT CMAKE_CROSSCOMPILING)
    enable_testing()

    # Add test cpp file
    add_executable(etap_passing_test
        unittests/etap_passingcases_unittest.cpp
    )
    target_include_directories(etap_passing_test
        PUBLIC
        include
    )
    target_link_libraries(etap_passing_test etap)
    add_test(etap_passing_test etap_passing_test)

    # Add test C file
    add_executable(etap_failing_test
        unittests/etap_failingcases_unittest.c
    )
    target_include_directories(etap_failing_test
        PUBLIC
        include
    )
    target_link_libraries(etap_failing_test etap)
    add_test(etap_failing_test etap_failing_test)

    # Add test for all setup/teardown and general execution flow
    add_executable(etap_infra_test
        unittests/etap_infra_unittest.cpp
    )
    target_include_directories(etap_infra_test
        PUBLIC
        include
    )
    target_link_libraries(etap_infra_test etap)
    add_test(etap_infra_test etap_infra_test)

    # Add test for minimal case
    add_executable(etap_minimal_test
        unittests/etap_minimal_unittest.cpp
    )
    target_include_directories(etap_minimal_test
        PUBLIC
        include
    )
    target_link_libraries(etap_minimal_test etap)
    add_test(etap_minimal_test etap_minimal_test)

    # Add test for passing ASSERT_TRUE()
    add_executable(etap_asserttrue_onpass_test
        unittests/etap_asserttrue_onpass_unittest.cpp
    )
    target_include_directories(etap_asserttrue_onpass_test
        PUBLIC
        include
    )
    target_link_libraries(etap_asserttrue_onpass_test etap)
    add_test(etap_asserttrue_onpass_test etap_asserttrue_onpass_test)

    # Add test for failing ASSERT_TRUE()
    add_executable(etap_asserttrue_onfail_test
        unittests/etap_asserttrue_onfail_unittest.cpp
    )
    target_include_directories(etap_asserttrue_onfail_test
        PUBLIC
        include
    )
    target_link_libraries(etap_asserttrue_onfail_test etap)
    add_test(etap_asserttrue_onfail_test etap_asserttrue_onfail_test)

    # Add test for passing EXPECT_TRUE()
    add_executable(etap_expecttrue_onpass_test
        unittests/etap_expecttrue_onpass_unittest.cpp
    )
    target_include_directories(etap_expecttrue_onpass_test
        PUBLIC
        include
    )
    target_link_libraries(etap_expecttrue_onpass_test etap)
    add_test(etap_expecttrue_onpass_test etap_expecttrue_onpass_test)

   # Add test for failing EXPECT_TRUE()
    add_executable(etap_expecttrue_onfail_test
        unittests/etap_expecttrue_onfail_unittest.cpp
    )
    target_include_directories(etap_expecttrue_onfail_test
        PUBLIC
        include
    )
    target_link_libraries(etap_expecttrue_onfail_test etap)
    add_test(etap_expecttrue_onfail_test etap_expecttrue_onfail_test)

     # Add test for passing ASSERT_FALSE()
    add_executable(etap_assertfalse_onpass_test
        unittests/etap_assertfalse_onpass_unittest.cpp
    )
    target_include_directories(etap_assertfalse_onpass_test
        PUBLIC
        include
    )
    target_link_libraries(etap_assertfalse_onpass_test etap)
    add_test(etap_assertfalse_onpass_test etap_assertfalse_onpass_test)

   # Add test for failing ASSERT_FALSE()
    add_executable(etap_assertfalse_onfail_test
        unittests/etap_assertfalse_onfail_unittest.cpp
    )
    target_include_directories(etap_assertfalse_onfail_test
        PUBLIC
        include
    )
    target_link_libraries(etap_assertfalse_onfail_test etap)
    add_test(etap_assertfalse_onfail_test etap_assertfalse_onfail_test)

    # finally the test to find them all and in the bash shell bind them.  this is to basically
    # do regression detection, NOTE the 'expected output' files need to be hand checked by a human
    # to validate they are correct, this test just checks re-running each test still produces the
    # _same_ output.
    add_test(NAME etap_check_all_tests
             COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/unittests/run_etap_unit_tests.sh ${CMAKE_CURRENT_SOURCE_DIR}/unittests
             WORKING_DIR ${CMAKE_CURRENT_BINARY_DIR})

endif()
