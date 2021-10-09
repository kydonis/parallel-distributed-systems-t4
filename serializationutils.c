#include <stdlib.h>
#include "serializationutils.h"
#include "stack.h"

void serializeStack(struct Stack *stack, uint32_t *serialized) {
    serialized[0] = stack->top;
    for (uint32_t i = 0; i < stack->top ; i += 1) {
        serialized[2 * i + 1] = stack->array[i]->x;
        serialized[2 * i + 2] = stack->array[i]->y;
    }
}

void deserializeToCoo(uint32_t *serialized, uint32_t *rowsCoo, uint32_t *colsCoo) {
    uint32_t size = serialized[0];
    for (uint32_t i = 0; i < size; i++) {
        rowsCoo[i] = serialized[2 * i + 1];
        colsCoo[i] = serialized[2 * i + 2];
    }
}
