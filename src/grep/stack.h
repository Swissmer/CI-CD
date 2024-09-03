#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 1
#define SIZE 8192

typedef struct stack {
  char **data;
  size_t size;
  size_t top;
} stack;

stack *createStack() {
  stack *out = NULL;
  out = malloc(sizeof(stack));
  out->size = INIT_SIZE;
  out->data = malloc(out->size * sizeof(char *));
  out->data[0] = calloc(SIZE, sizeof(char *));
  out->top = 0;
  return out;
}

void deleteStack(stack *stac) {
  stac->top = stac->size;
  for (size_t i = 0; i < stac->size; i++) {
    free(stac->data[i]);
  }
  free(stac->data);
  free(stac);
  stac = NULL;
}

void resize(stack *stack) {
  stack->size += 1;
  stack->data = realloc(stack->data, stack->size * sizeof(char *));
  stack->data[stack->top] = calloc(SIZE, sizeof(char *));
}

void push(stack *stack, char *value) {
  if (stack->top >= stack->size) {
    resize(stack);
  }
  char *ptr = strdup(value);
  memcpy(stack->data[stack->top], ptr, strlen(value) + 1);
  stack->top++;
  free(ptr);
}

void push_f(stack *stack, char *value) {
  if (stack->top >= stack->size) {
    resize(stack);
  }
  memcpy(stack->data[stack->top], value, strlen(value));
  stack->top++;
}

char *pop(stack *stack) {
  stack->top--;
  return stack->data[stack->top];
}

char *pop_o(stack *stack) { return stack->data[stack->top++]; }

char *peek(const stack *stack) { return stack->data[stack->top - 1]; }

void changeSize(stack *stack) { stack->top = stack->size; }