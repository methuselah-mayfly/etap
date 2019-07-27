#ifndef __TAPTEST_H_
#define __TAPTEST_H_

/**
   This is a suite for doing unit tests on the POSIX
   and/or the embedded target.  It uses the 'Test Anything Protocol'
   (https://testanything.org/).  Tests linked against this library
   will spit TAP compliant results out of stdio.
*/


// todo: look up https://www.npmjs.com/package/tap-junit

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "assert.h"

typedef int test_function(void);

typedef struct {
  const char * desc;
  test_function * ptest_func;
} tap_test;

extern tap_test* tap_test_list[];
  //extern int __current_test_index;  // for use by macros, do not use
void tt_report_failure(const char *);
void etap_init_bsp(int argc, const char * argv[]);

#define ETAP_USE_DEFAULT_BSP void etap_init_bsp(int argc, const char * argv[]){}

#define TEST_START(p) int __taptest_local_result = 1
#define TEST_END(p) return __taptest_local_result

#define EXPECT_TRUE(p)                 \
  do                                   \
    {                                  \
      __taptest_local_result &= (p);   \
    }while(0)

#define ASSERT_TRUE(p)                 \
  do                                   \
    {                                  \
      if (!(p)) return 0;              \
    }while(0)

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#define EXPECT_FALSE(p)                \
  do                                   \
    {                                  \
      int val = (p);                                                   \
      if (val)                                                          \
     { tt_report_failure(LINE_STRING); __taptest_local_result &= !(val); } \
    }while(0)

#define ASSERT_FALSE(p)                \
  do                                   \
    {                                  \
  int val = (p); \
  if (val) { tt_report_failure("unexpected MARTIANS"##_LINE_);  return 0};  \
    }while(0)

#ifdef __cplusplus
}
#endif

///// START OF INCLUDED (SHUDDER) CODE DEFINITIONS

int __current_test_index;  // for use by macros, do not use

static int num_tests()
{
    int num_tests = 0;
    tap_test ** ptest = tap_test_list;

    while (*ptest != (void*)0)
        {
            num_tests++;
            ptest++;
        }

    return num_tests;
}

static void emit_tap_version()
{
    puts("TAP version 13");
}

static void emit_tap_plan()
{
    printf("1..%d\n", num_tests());
}

static int run_single_test(tap_test * test, int index)
{
    __current_test_index = index;  //used by test macros

    assert(test->ptest_func != (void*)0);
    int isok = test->ptest_func();

    printf("%sok %i - %s\n", (isok) ? "" : "not ", index, test->desc);

    return isok;
}

static int global_result_isok = ! 0;

// TODO:
// 1) convert to HEADER ONLY VERSION a la catch2 (code in header ok for test framework)
// 2) add macro to call/stub bsp for hal_init  ETAP_NO_BSP;
// 3) do tests that check via bash script tap outputon POSIX is all fail, all pass for test tests

int main(int argc, const char * argv[]) {
    // set up HAL device name mappings, also can override defaults in POSIX
    // this also sets unit test serial port via the -s flag
    etap_init_bsp(argc, argv);

    emit_tap_version();
    emit_tap_plan();

    for (int i = 0; i < num_tests(); i++)
        {
            // call test, print results, collate global result.
            global_result_isok &= run_single_test(tap_test_list[i], i+1);
        }

    // BASH return code is ZERO for good, i.e. isok -> 0
    return ! global_result_isok;
}

void tt_report_failure(const char *str)
{
    printf("# TEST %i: FAIL [%s]\n", __current_test_index, str);
}

#endif // __TAPTEST_H_
