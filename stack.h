#ifndef PARALLEL_DISTRIBUTED_SYSTEMS_T4_ARRAYLIST_H
#define PARALLEL_DISTRIBUTED_SYSTEMS_T4_ARRAYLIST_H

#include <stdlib.h>

struct Pair {
    uint32_t x;
    uint32_t y;
};

struct Stack {
    uint32_t top;
    struct Pair **array;
};

struct Stack *createStack();

int isEmpty(struct Stack *stack);

void push(struct Stack *stack, struct Pair *item);

struct Pair *pop(struct Stack *stack);

struct Pair **getArrayCopy(struct Stack *stack);

#endif //PARALLEL_DISTRIBUTED_SYSTEMS_T4_ARRAYLIST_H
