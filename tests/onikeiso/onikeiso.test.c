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

    not_gate.inputs[0].value = TRUE;
    propagate(&not_gate);
    TEST_ASSERT_EQUAL(FALSE, not_gate.outputs[0].value);

    free_gate(&not_gate);
}

void identity_gate_test(void) {
    Gate identity_gate;
    make_identity_gate(&identity_gate);

    TEST_ASSERT_EQUAL(UNDEFINED, identity_gate.inputs[0].value);
    TEST_ASSERT_EQUAL(UNDEFINED, identity_gate.outputs[0].value);
    TEST_ASSERT_EQUAL(INPUT, identity_gate.inputs[0].type);
    TEST_ASSERT_EQUAL(OUTPUT, identity_gate.outputs[0].type);

    identity_gate.inputs[0].value = FALSE;
    propagate(&identity_gate);
    TEST_ASSERT_EQUAL(FALSE, identity_gate.outputs[0].value);

    identity_gate.inputs[0].value = TRUE;
    propagate(&identity_gate);
    TEST_ASSERT_EQUAL(TRUE, identity_gate.outputs[0].value);

    free_gate(&identity_gate);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(not_gate_test);
    RUN_TEST(identity_gate_test);
    return UNITY_END();
}
