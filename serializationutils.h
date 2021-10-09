#ifndef PARALLEL_DISTRIBUTED_SYSTEMS_T4_SERIALIZATIONUTILS_H
#define PARALLEL_DISTRIBUTED_SYSTEMS_T4_SERIALIZATIONUTILS_H

#include <stdlib.h>
#include "stack.h"

void serializeStack(struct Stack *stack, uint32_t *serialized);

void deserializeToCoo(uint32_t *serialized, uint32_t *rowsCoo, uint32_t *colsCoo);

#endif //PARALLEL_DISTRIBUTED_SYSTEMS_T4_SERIALIZATIONUTILS_H
