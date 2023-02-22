#include "calc_module.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data_structures/stack.h"
#include "../parse_module/parser.h"
#define EPS 1e-12

double do_operation(char op, double a, double b) {
  return op == '*'   ? a * b
         : op == '/' ? fabs(b) < EPS ? 100 : a / b
         : op == '+' ? a + b
         : op == '-' ? a - b
         : op == '^' ? pow(a, b)
                     : 100;
}

double do_func(char f, double a) {
  return f == 's'   ? sin(a)
         : f == 'c' ? cos(a)
         : f == 't' ? fabs(cos(a)) > EPS ? tan(a) : 100
         : f == 'g' ? fabs(sin(a)) > EPS ? tan(M_PI / 2 - a) : 100
         : f == 'q' ? a >= EPS ? sqrt(a) : 100
         : f == 'l' ? a > EPS ? log(a) : 100
         : f == '~' ? a * -1
                    : 100;
}

double calc(char *rpn_exp, double x) {
  char *token = strtok(rpn_exp, " ");
  int nan_flag = 0;
  char_lf passed_x;
  passed_x.num = x;
  char_lf y;
  y.num = 0;
  char_lf result;
  struct node *stack = NULL;
  while (token && !nan_flag) {
    if (sscanf(token, "%lf", &y.num) != 0) {
      stack = push(stack, y);
    } else {
      stack = handle_operation(token, stack, passed_x, &nan_flag);
    }
    token = strtok(NULL, " ");
  }
  if (!nan_flag) {
    result.num = stack->data.num;
  } else {
    result.num = 100;
  }
  free(stack);
  return result.num;
}

node *handle_operation(char *token, node *stack, char_lf x, int *flag) {
  if (*token == 'x') {
    stack = push(stack, x);
  } else {
    char_lf a;
    char_lf result;
    if (is_op(*token) && *token != '~') {
      char_lf b;
      stack = pop(stack, &b);
      stack = pop(stack, &a);
      result.num = do_operation(*token, a.num, b.num);
    } else {
      stack = pop(stack, &a);
      result.num = do_func(*token, a.num);
    }
    if (result.num == 100) *flag = 1;
    stack = push(stack, result);
  }
  return stack;
}
