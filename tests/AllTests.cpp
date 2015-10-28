#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, const char** av) {
  int result = RUN_ALL_TESTS(ac, av);
  return result;
}

