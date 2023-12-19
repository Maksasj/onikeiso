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

void and_gate_test(void) {
    Gate and_gate;
    make_and_gate(&and_gate);

    and_gate.inputs[0].value = TRUE;
    and_gate.inputs[1].value = TRUE;
    propagate(&and_gate);
    TEST_ASSERT_EQUAL(TRUE, and_gate.outputs[0].value);

    and_gate.inputs[0].value = TRUE;
    and_gate.inputs[1].value = FALSE;
    propagate(&and_gate);
    TEST_ASSERT_EQUAL(FALSE, and_gate.outputs[0].value);

    free_gate(&and_gate);
}

void nand_gate_test(void) {
    Gate nand_gate;
    make_nand_gate(&nand_gate);

    nand_gate.inputs[0].value = TRUE;
    nand_gate.inputs[1].value = TRUE;
    propagate(&nand_gate);
    TEST_ASSERT_EQUAL(FALSE, nand_gate.outputs[0].value);

    nand_gate.inputs[0].value = TRUE;
    nand_gate.inputs[1].value = FALSE;
    propagate(&nand_gate);
    TEST_ASSERT_EQUAL(TRUE, nand_gate.outputs[0].value);

    free_gate(&nand_gate);
}

void or_gate_test(void) {
    Gate or_gate;
    make_or_gate(&or_gate);

    or_gate.inputs[0].value = FALSE;
    or_gate.inputs[1].value = FALSE;
    propagate(&or_gate);
    TEST_ASSERT_EQUAL(FALSE, or_gate.outputs[0].value);

    or_gate.inputs[0].value = TRUE;
    or_gate.inputs[1].value = FALSE;
    propagate(&or_gate);
    TEST_ASSERT_EQUAL(TRUE, or_gate.outputs[0].value);

    free_gate(&or_gate);
}

void nor_gate_test(void) {
    Gate nor_gate;
    make_nor_gate(&nor_gate);

    nor_gate.inputs[0].value = FALSE;
    nor_gate.inputs[1].value = FALSE;
    propagate(&nor_gate);
    TEST_ASSERT_EQUAL(TRUE, nor_gate.outputs[0].value);

    nor_gate.inputs[0].value = TRUE;
    nor_gate.inputs[1].value = FALSE;
    propagate(&nor_gate);
    TEST_ASSERT_EQUAL(FALSE, nor_gate.outputs[0].value);

    free_gate(&nor_gate);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(not_gate_test);
    RUN_TEST(identity_gate_test);
    RUN_TEST(and_gate_test);
    RUN_TEST(nand_gate_test);
    RUN_TEST(or_gate_test);
    RUN_TEST(nor_gate_test);
    return UNITY_END();
}
