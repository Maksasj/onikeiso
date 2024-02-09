#include "unity.h"
#include "onikeiso.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void initial_test(void) {
    Gate entry;
    make_identity_gate(&entry);

    Gate not;
    make_not_gate(&not);

    entry.inputs[0].value = TRUE;
    entry.inputs[0].self = &entry;
    entry.inputs[0].target = NULL;

    entry.outputs[0].value = UNDEFINED;
    entry.outputs[0].self = &entry;
    entry.outputs[0].target = &not.inputs[0];

    not.inputs[0].value = UNDEFINED;
    not.inputs[0].self = &not;
    not.inputs[0].target = NULL;

    not.outputs[0].value = UNDEFINED;
    not.outputs[0].self = &not;
    not.outputs[0].target = NULL;

    propagate(&entry);

    TEST_ASSERT_EQUAL(FALSE, not.outputs[0].value);

    free_gate(&entry);
    free_gate(&not);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(initial_test);

    return UNITY_END();
}
