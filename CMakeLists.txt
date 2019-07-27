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
endif()