#include "etap.h"

ETAP_USE_DEFAULT_BSP;

/**
   The purpose of these tests is to exercise every
   test macro to demonstrate that it FAILS when
   expected, i.e. that it meets the negative criteria.
*/

int t1_body()
{
  TEST_START();

  EXPECT_TRUE( (1 == 8) );
  EXPECT_FALSE( (8 == 8) );

  TEST_END();
}

int t2_body()
{
  TEST_START();

  EXPECT_TRUE(0);

  TEST_END();
}

tap_test t1 =   {
   "a test!",
   &t1_body,
  };

tap_test t2 =
   {
   "a (failing) test!",
   &t2_body,
  };

tap_test * tap_test_list[] =
  {
   &t1,
   &t2,
   0,
  };
