#include "onikeiso.h"
#include <stdlib.h>
#include <stdio.h>

void make_input_pins(Gate *gate, size_t size) {
    gate->inputs = malloc(size * sizeof(Pin));
    gate->inputs_count = size;

    for (size_t i = 0; i < size; ++i) {
        gate->inputs[i].value = UNDEFINED;
        gate->inputs[i].type = INPUT;
    }
}

void make_output_pins(Gate *gate, size_t size) {
    gate->outputs = malloc(size * sizeof(Pin));
    gate->outputs_count = size;

    for (size_t i = 0; i < size; ++i) {
        gate->outputs[i].value = UNDEFINED;
        gate->outputs[i].type = OUTPUT;
    }
}

void update_not_gate(Gate *self) {
    if (self->inputs[0].value == TRUE) {
        self->outputs[0].value = FALSE;
        if (self->outputs[0].target != NULL) {
            self->outputs[0].target->value = self->outputs[0].value;
        }
    } else if (self->inputs[0].value == FALSE) {
        self->outputs[0].value = TRUE;
        if (self->outputs[0].target != NULL) {
            self->outputs[0].target->value = self->outputs[0].value;
        }
    }
}

void update_identity_gate(Gate *self) {
    self->outputs[0].value = self->inputs[0].value;

    if (self->outputs[0].target != NULL) {
        self->outputs[0].target->value = self->outputs[0].value;
    }
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
    make_input_pins(gate, 1);
    make_output_pins(gate, 1);

    gate->update = &update_not_gate;
}

void make_identity_gate(Gate *gate) {
    make_not_gate(gate);
    gate->update = update_identity_gate;
}

void make_and_gate(Gate *gate) {
    make_input_pins(gate, 2);
    make_output_pins(gate, 1);

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
    Queue queue;
    create_queue(&queue, 1000);

    queue_push(&queue, gate);

    while (!queue_empty(&queue)) {
        Gate *current = queue_pop(&queue);

        current->update(current);

        for (size_t i = 0; i < current->outputs_count; ++i) {
            if (current->outputs[i].target != NULL) {
                queue_push(&queue, current->outputs[i].target->self);
            }
        }
    }
}
