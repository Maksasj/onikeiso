#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_you_want_to_test(void) {
    // your test code here
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_you_want_to_test);
    return UNITY_END();
}
