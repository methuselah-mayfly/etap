#include "etap.h"

/**
   The purpose of these tests is to verify
   that the ASSERT_TRUE() exits early for
   the failing case.
*/

ETAP_FULL;

ETAP_USE_DEFAULT_BSP;

static int i;

ETAP_DEFINE_SETUP(){
  printf("# SETUP for %i\n", i=__current_test_index);
}

ETAP_DEFINE_TEARDOWN(){
  printf("# TEARDOWN for %i\n", i);
}

ETAP_SUITE_START("Test that ASSERT_TRUE() exits on fail.");

ETAP_TEST("one, should complete"){
    ASSERT_TRUE(1);
}

ETAP_TEST("two, should abort and return fail for whole suite"){
    ASSERT_TRUE(0);
}

ETAP_TEST("three, should never run"){
    EXPECT_TRUE(1);
}

ETAP_SUITE_END;
