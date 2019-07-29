#include "etap.h"

/**
   The purpose of these tests is to exercise
   the setup, teardown, and test reporting.
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

ETAP_SUITE_START("Test that the setup/teardown and test reports run as expected.");

ETAP_TEST("Test one"){
    ETAP_PRINTF("We should have setup and teardown bracketing this test, which should PASS.\n");
    EXPECT_TRUE(1);
}

ETAP_TEST("Test two"){
    EXPECT_TRUE(1);
}

ETAP_TEST("Test three"){
    EXPECT_TRUE(1);
}

ETAP_TEST("Test four and final"){
    EXPECT_TRUE(1);
}

ETAP_SUITE_END;
