#include "etap.h"

/**
   The purpose of these tests is to check
   the minimal setup works.
*/

ETAP_MINIMAL;
ETAP_USE_DEFAULT_BSP;

ETAP_SUITE_START("Test Minimal Setup");

ETAP_TEST("Minimal"){
    EXPECT_TRUE(1);
}

ETAP_SUITE_END;
