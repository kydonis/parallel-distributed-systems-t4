#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "stack.h"

double measureTimeForRunnable(void (* runnable) (uint32_t *, uint32_t *, uint32_t *, uint32_t *, struct Stack *, uint32_t), uint32_t *arg1, uint32_t *arg2, uint32_t *arg3, uint32_t *arg4, struct Stack *arg5, uint32_t arg6);

#endif //T1_TIMER_H
