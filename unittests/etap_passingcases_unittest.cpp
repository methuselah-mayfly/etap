#include "etap.h"

/**
   The purpose of these tests is to exercise every
   test macro to demonstrate that it PASSES when
   expected, i.e. that it meets the positive criteria.
*/

// ETAP_MINIMAL;
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

ETAP_TEST("expect true passes when TRUE"){
    ETAP_PRINTF("bob and his amazing chainsaw. %i  %i \n", 7, 3);
    EXPECT_TRUE( (8 == 8) );
    EXPECT_FALSE( (1 == 8) );
    EXPECT_TRUE(1);
}

ETAP_SUITE_END;
