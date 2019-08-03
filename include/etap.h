#ifndef __ETAP_H_
#define __ETAP_H_

/**
   This is a suite for doing unit tests on the POSIX
   and/or the embedded target.  It uses the 'Test Anything Protocol'
   (https://testanything.org/).  Tests linked against this library
   will spit TAP compliant results out of stdio.
*/

#ifndef __COUNTER__
#error    # this library depends upon the non standard preprocessor macro __COUNTER__, which gcc, clang both support
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "assert.h"

//  must be used in a function body
#define ETAP_TEST(desc)                                        \
  __current_test_index++;                                      \
  if (__current_test_index != 1) {                             \
    do_after_single_test_processing(__current_test_index - 1); \
  }                                                            \
  __etap_local_result_isok = 1;                                \
  do_setup();                                                  \
  update_test_details(desc, __COUNTER__);

#define ETAP_PRINTF(...) printf("# " __VA_ARGS__)

// is plonked at file scope, sets sd directly.
// must be assignment, can't call func as not in statement!
#define ETAP_SUITE_START(desc) \
  const char * sd = desc;      \
  void dotests() {

#define ETAP_SUITE_END      \
  }                         \
static int num_tests(void){ \
  return __COUNTER__;       \
}

#define ETAP_DEFINE_SETUP() \
  void do_setup(void)

#define ETAP_DEFINE_TEARDOWN() \
  void do_teardown(void)

// minimal provides stubs for setup/teardown
#define ETAP_MINIMAL     \
  void do_setup(void){}; \
  void do_teardown(void){}

#define ETAP_FULL

extern const char * sd;


void do_setup(void);
void do_teardown(void);

static void dummy(const char *desc, int cnt){};

const char * test_desc;
int __current_test_index;  // current test index, from 1, 0 is no tests run yet

void update_test_details(const char *desc, int dummy);
void update_test_details(const char *desc, int dummy)
{
  test_desc = desc;
  printf("# running test %i [%s]\n", __current_test_index, test_desc);
}

void dotests(void);

static int num_tests(void);

typedef void test_function(void);

typedef struct {
  const char * desc;
  test_function * ptest_func;
} tap_test;

int __etap_local_result_isok;
void tt_report_failure(const char *pred, const char *location_str);
void etap_init_bsp(int argc, const char * argv[]);

#define ETAP_USE_DEFAULT_BSP void etap_init_bsp(int argc, const char * argv[]){}

// thanks to http://www.decompile.com/cpp/faq/file_and_line_error_string.htm
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

#define EXPECT_TRUE(p)                                         \
  do                                                           \
    {                                                          \
      int val = (p);                                           \
      __etap_local_result_isok &= (val);                       \
      if (! val) {                                             \
        tt_report_failure("EXPECT_TRUE(" TOSTRING(p) ")", AT); \
      }                                                        \
    }while(0)

#define ASSERT_TRUE(p)                                                 \
  do                                                                   \
    {                                                                  \
      int val = (p);                                                   \
      __etap_local_result_isok &= (val);                               \
      if (! val) {                                                     \
        tt_report_failure("ASSERT_TRUE(" TOSTRING(p) ")", AT); return; \
      }                                                                \
    }while(0)

#define EXPECT_FALSE(p)                                             \
  do                                                                \
    {                                                               \
      int val = (p);                                                \
      __etap_local_result_isok &= !(val);                           \
      if (val)                                                      \
        { tt_report_failure("EXPECT_FALSE(" TOSTRING(p) ")", AT); } \
    }while(0)

#define ASSERT_FALSE(p)                                                 \
  do                                                                    \
    {                                                                   \
      int val = (p);                                                    \
      __etap_local_result_isok &= !(val);                               \
      if ( val) {                                                       \
        tt_report_failure("ASSERT_FALSE(" TOSTRING(p) ")", AT); return; \
      }                                                                 \
    }while(0)


#ifdef __cplusplus
}
#endif

///// START OF INCLUDED (SHUDDER) CODE DEFINITIONS

static int __etap_global_result_isok = ! 0;

static void emit_tap_version()
{
  puts("TAP version 13");
}

static void emit_tap_plan(void)
{
  printf("1..%d\n", num_tests());
}

static void emit_tap_result(int test_num)
{
  printf("%sok - %d\n", (! __etap_local_result_isok) ? "not " : "", test_num);
}

static void emit_tap_suite_desc()
{
  printf("# Test Suite: %s\n", sd);
}

static void do_after_single_test_processing(int test_index)
{
  do_teardown();                                         // final teardown for last test.
  emit_tap_result(test_index);                           // test result for last test run
  __etap_global_result_isok &= __etap_local_result_isok; // fold in global test result from last test
}

int main(int argc, const char * argv[]) {
  // set up HAL device name mappings, also can override defaults in POSIX
  // this can also set unit test serial port via the -s flag
  etap_init_bsp(argc, argv);

  emit_tap_version();
  emit_tap_suite_desc();
  emit_tap_plan();

  __current_test_index = 0;
  dotests();
  do_after_single_test_processing(__current_test_index);

  // BASH return code is ZERO for good, i.e. isok -> 0
  return ! __etap_global_result_isok;
}

void tt_report_failure(const char *pred, const char *location_str)
{
  printf("#FAILED %s: %s\n", pred, location_str);
}

#endif // __ETAP_H_
