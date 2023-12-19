#ifndef ONIKEISO_H
#define ONIKEISO_H

#include "stdbool.h"

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

typedef struct {
    PinValue value;
    PinType type;
} Pin;

typedef struct Gate Gate;

struct Gate {
    Pin *inputs;
    Pin *outputs;
    void (*update)(Gate* self);
};

void make_not_gate(Gate *gate);

void make_identity_gate(Gate *gate);

void free_gate(Gate *gate);

void propagate(Gate *gate);

#endif
