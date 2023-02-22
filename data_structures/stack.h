#ifndef SRC_DATA_STRUCTURES_STACK_H_
#define SRC_DATA_STRUCTURES_STACK_H_
#include <stdlib.h>

typedef union char_lf {
  char ch;
  double num;
} char_lf;

typedef struct node {
  char_lf data;
  struct node* next;
} node;

node* init(char_lf n);
node* push(node* stack, char_lf n);
node* pop(node* stack, char_lf* l);
void destroy(node* stack);

#endif  // SRC_DATA_STRUCTURES_STACK_H_
