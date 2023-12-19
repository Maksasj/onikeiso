#include "unity.h"
#include "onikeiso.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void not_gate_test(void) {
    Gate not_gate;
    make_not_gate(&not_gate);

    TEST_ASSERT_EQUAL(UNDEFINED, not_gate.inputs[0].value);
    TEST_ASSERT_EQUAL(UNDEFINED, not_gate.outputs[0].value);
    TEST_ASSERT_EQUAL(INPUT, not_gate.inputs[0].type);
    TEST_ASSERT_EQUAL(OUTPUT, not_gate.outputs[0].type);

    not_gate.inputs[0].value = FALSE;
    propagate(&not_gate);

    TEST_ASSERT_EQUAL(TRUE, not_gate.outputs[0].value);

    free_gate(&not_gate);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(not_gate_test);
    return UNITY_END();
}
