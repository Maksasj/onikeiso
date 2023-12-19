#include "onikeiso.h"
#include <stdlib.h>

void make_input_pin(Pin *pin) {
    pin->value = UNDEFINED;
    pin->type = INPUT;
}

void make_output_pin(Pin *pin) {
    pin->value = UNDEFINED;
    pin->type = OUTPUT;
}

void update_not_gate(Gate *self) {
    self->outputs[0].value = !self->inputs[0].value;
}

void make_not_gate(Gate *gate) {
    gate->inputs = malloc(1 * sizeof(Pin));
    gate->outputs = malloc(1 * sizeof(Pin));

    make_input_pin(&gate->inputs[0]);
    make_output_pin(&gate->outputs[0]);
    gate->update = &update_not_gate;
}

void free_gate(Gate *gate) {
    free(gate->inputs);
    free(gate->outputs);
}

void propagate(Gate *gate) {
    gate->update(gate);
}
