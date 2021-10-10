#include <stdlib.h>
#include "serializationutils.h"
#include "stack.h"

void serializeStack(struct Stack *stack, uint32_t *serialized, uint32_t nc) {
    serialized[0] = stack->top;
    serialized[1] = nc;
    for (uint32_t i = 0; i < stack->top ; i += 1) {
        serialized[2 * i + 2] = stack->array[i]->x;
        serialized[2 * i + 3] = stack->array[i]->y;
    }
}

void deserializedIntoStack(uint32_t *serialized, struct Stack *stack) {
    uint32_t size = serialized[0];
    for (uint32_t i = 0; i < size; i++) {
        struct Pair *p = (struct Pair *) malloc(sizeof(struct Pair));
        p->x = serialized[2 * i + 2];
        p->y = serialized[2 * i + 3];
        push(stack, p);
    }
}

void deserializeToCoo(uint32_t *serialized, uint32_t *rowsCoo, uint32_t *colsCoo, uint32_t *nc) {
    uint32_t size = serialized[0];
    *nc = serialized[1];
    for (uint32_t i = 0; i < size; i++) {
        rowsCoo[i] = serialized[2 * i + 2];
        colsCoo[i] = serialized[2 * i + 3];
    }
}
