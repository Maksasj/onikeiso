//#include "stdbool.h"
//
//typedef enum {
//    TRUE,
//    FALSE,
//    UNDEFINED,
//    ERROR
//} Value;
//
//typedef enum {
//    INPUT,
//    OUTPUT
//} Type;
//
//struct Gate;
//
//typedef struct {
//    Value value;
//    struct Gate *parent;
//    Type type;
//    struct Pin *connection;
//
//    bool calculated;
//} Pin;
//
//typedef struct {
//    Pin *inputs;
//    Pin *outputs;
//    void *update;
//} Gate;
//
//void propagate(Gate *gate, Pin *newInputs) {
//    gate->inputs = newInputs;
//    gate->update(gate); // outputs will be updated
//    for (auto out : gate->outputs) {
//        out->connection->value = out->value;
//        Gate *destinationGate = out->connection->parent;
//        propagate(destinationGate, destinationGate->inputs);
//    }
//}
