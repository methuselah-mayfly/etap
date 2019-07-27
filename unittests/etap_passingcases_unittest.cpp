#include "etap.h"

ETAP_USE_DEFAULT_BSP;

/**
   The purpose of these tests is to exercise every
   test macro to demonstrate that it PASSES when
   expected, i.e. that it meets the positive criteria.
*/

int passing_test()
{
  TEST_START();

  EXPECT_TRUE(1);

  TEST_END();
}


int passing_test2()
{
  TEST_START();

  EXPECT_TRUE( (3 == 3) );
  EXPECT_TRUE(1);

  TEST_END();
}

tap_test t1 =   {
   "a test!",
   &passing_test,
  };

tap_test t2 =
   {
   "an other test!",
   &passing_test2,
  };

tap_test t3 =
   {
   "a THIRD passing test!",
   &passing_test,
  };

tap_test * tap_test_list[] =
  {
   &t1,
   &t2,
   &t3,
   0,
  };
