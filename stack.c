#include <stdlib.h>

uint8_t countBits(uint8_t num) {
    uint8_t bits = 0;
    while (num) {
        bits += num & 1;
        num >>= 1;
    }
    return bits;
}

struct Pair {
    uint8_t x;
    uint8_t y;
};

struct Stack {
    uint8_t top;
    struct Pair *array;
};

struct Stack *createStack() {
    struct Stack *stack = (struct Stack *) malloc(sizeof(struct Stack));
    stack->top = 0;
    stack->array = (struct Pair *) malloc(0);
    return stack;
}

int isEmpty(struct Stack *stack) {
    return stack->top == 0;
}

void push(struct Stack *stack, struct Pair item) {
    if (countBits(stack->top) == 1) {
        stack->array = realloc(stack->array, (stack->top << 1) * sizeof(struct Pair));
    }
    stack->top++;
    stack->array[stack->top - 1] = item;
}

struct Pair pop(struct Stack *stack) {
    if (stack->top == 0) {
        exit(1);
    }
    struct Pair val = stack->array[stack->top - 1];
    stack->top--;
    if (countBits(stack->top) == 1) {
        stack->array = realloc(stack->array, stack->top * sizeof(struct Pair));
    }
    return val;
}

struct Pair *getArrayCopy(struct Stack *stack) {
    struct Pair *data = (struct Pair *) malloc(stack->top * sizeof(struct Pair));
    for (int i = 0; i < stack->top; i++) {
        data[i] = stack->array[i];
    }
    return data;
}
