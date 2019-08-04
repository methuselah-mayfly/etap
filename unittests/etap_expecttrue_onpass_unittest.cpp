#include "etap.h"

/**
   The purpose of these tests is to verify
   that the EXPECT_TRUE() works
   the passing case.
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

ETAP_SUITE_START("Test that all expected passes actually PASS!");

ETAP_TEST("one, should complete"){
    EXPECT_TRUE(1);
}

ETAP_TEST("two, should complete"){
    EXPECT_TRUE(1);
}

ETAP_TEST("three, should complete"){
    EXPECT_TRUE(1);
}

ETAP_SUITE_END;
