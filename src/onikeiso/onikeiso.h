#ifndef ONIKEISO_H
#define ONIKEISO_H

#include "queue.h"

typedef enum {
    TRUE,
    FALSE,
    UNDEFINED,
    ERROR
} PinValue;

typedef enum {
    INPUT,
    OUTPUT
} PinType;

typedef struct Gate Gate;

typedef struct Pin Pin;

struct Pin {
    PinValue value;
    PinType type;
    Gate *self;
    Pin *target;
};

struct Gate {
    Pin *inputs;
    size_t inputs_count;
    Pin *outputs;
    size_t outputs_count;
    void (*update)(Gate* self);
};

void make_not_gate(Gate *gate);

void make_identity_gate(Gate *gate);

void make_and_gate(Gate *gate);
void make_nand_gate(Gate *gate);

void make_or_gate(Gate *gate);
void make_nor_gate(Gate *gate);

void free_gate(Gate *gate);

void propagate(Gate *gate);

#endif
