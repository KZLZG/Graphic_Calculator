#ifndef SRC_CALC_MODULE_CALC_MODULE_H_
#define SRC_CALC_MODULE_CALC_MODULE_H_
#include "../data_structures/stack.h"

//   Получает:
// Возвращает: результат вычисления выражения
double do_operation(char op, double a, double b);
double do_func(char f, double a);
double calc(char *rpn_exp, double x);
node *handle_operation(char *token, node *stack, char_lf x, int *flag);

#endif  // SRC_CALC_MODULE_CALC_MODULE_H_
