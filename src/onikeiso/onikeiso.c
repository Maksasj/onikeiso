#include "onikeiso.h"
#include <stdlib.h>

void make_input_pins(Pin *pins, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        pins[i].value = UNDEFINED;
        pins[i].type = INPUT;
    }
}

void make_output_pins(Pin *pins, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        pins[i].value = UNDEFINED;
        pins[i].type = OUTPUT;
    }
}

void update_not_gate(Gate *self) {
    self->outputs[0].value = !self->inputs[0].value;
}

void update_identity_gate(Gate *self) {
    self->outputs[0].value = self->inputs[0].value;
}

void update_and_gate(Gate *self) {
    if (self->inputs[0].value == TRUE && self->inputs[1].value == TRUE) {
        self->outputs[0].value = TRUE;
    } else {
        self->outputs[0].value = FALSE;
    }
}

void update_nand_gate(Gate *self) {
    if (self->inputs[0].value == TRUE && self->inputs[1].value == TRUE) {
        self->outputs[0].value = FALSE;
    } else {
        self->outputs[0].value = TRUE;
    }
}

void update_or_gate(Gate *self) {
    if (self->inputs[0].value == TRUE || self->inputs[1].value == TRUE) {
        self->outputs[0].value = TRUE;
    } else {
        self->outputs[0].value = FALSE;
    }
}

void update_nor_gate(Gate *self) {
    if (self->inputs[0].value == TRUE || self->inputs[1].value == TRUE) {
        self->outputs[0].value = FALSE;
    } else {
        self->outputs[0].value = TRUE;
    }
}

void make_not_gate(Gate *gate) {
    gate->inputs = malloc(1 * sizeof(Pin));
    gate->outputs = malloc(1 * sizeof(Pin));

    make_input_pins(gate->inputs, 1);
    make_output_pins(gate->outputs, 1);

    gate->update = &update_not_gate;
}

void make_identity_gate(Gate *gate) {
    make_not_gate(gate);
    gate->update = update_identity_gate;
}

void make_and_gate(Gate *gate) {
    gate->inputs = malloc(2 * sizeof(Pin));
    gate->outputs = malloc(1 * sizeof(Pin));

    make_input_pins(gate->inputs, 2);
    make_output_pins(gate->outputs, 1);

    gate->update = &update_and_gate;
}

void make_nand_gate(Gate *gate) {
    make_and_gate(gate);
    gate->update = update_nand_gate;
}

void make_or_gate(Gate *gate) {
    make_and_gate(gate);
    gate->update = &update_or_gate;
}

void make_nor_gate(Gate *gate) {
    make_and_gate(gate);
    gate->update = &update_nor_gate;
}

void free_gate(Gate *gate) {
    free(gate->inputs);
    free(gate->outputs);
}

void propagate(Gate *gate) {
    gate->update(gate);
}
