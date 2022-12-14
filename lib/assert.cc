#include "lib/assert.h"

#include "kern/sys.h"
#include "lib/bwio.h"
#include "lib/io.h"
#include "user/sys.h"
#include "user/task.h"

void __k_assert_func(const char* file, int line, const char* func,
                     const char* cond) {
  bwprintf(COM2,
           "\033[31m"
           "Assertion failed at %s:%d\n\r"
           "Function: %s\n\r"
           "Condition: %s\n\r"
           "\033[0m",
           file, line, func, cond);
  kExit();
}

void __assert_func(const char* file, int line, const char* func,
                   const char* cond) {
  bwprintf(COM2,
           "\033[31m"
           "Assertion failed at %s:%d\n\r"
           "Function: %s\n\r"
           "Condition: %s\n\r"
           "\033[0m",
           file, line, func, cond);
  shutdown();
}