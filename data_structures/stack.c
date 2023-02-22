#include "stack.h"

node* init(char_lf n) {
  node* stack;
  stack = malloc(sizeof(node));
  stack->data = n;
  stack->next = NULL;
  return stack;
}

node* push(node* stack, char_lf n) {
  if (stack == NULL) {
    stack = init(n);
  } else {
    node* tmp;
    tmp = malloc(sizeof(node));
    tmp->data = n;
    tmp->next = stack;
    stack = tmp;
  }
  return stack;
}

node* pop(node* stack, char_lf* l) {
  if (stack != NULL) {
    node* tmp;
    tmp = stack->next;
    *l = stack->data;
    free(stack);
    stack = tmp;
  }
  return stack;
}

void destroy(node* stack) {
  while (stack) {
    node* tmp = stack;
    stack = stack->next;
    free(tmp);
  }
}
