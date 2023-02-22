#ifndef SRC_PARSE_MODULE_PARSER_H_
#define SRC_PARSE_MODULE_PARSER_H_
#include "../data_structures/stack.h"
#include <stdlib.h>
#include <string.h>

//   Получает: инфиксную форму выражения
// Возвращает: результат операции (1 - успех, 0 - неудача) и
//             формирует строку, записанную в обратной польской нотации
int exp_to_rpn(char *expression, char **result);

//   Получает: указатель на текущий элемент цикла обхода строки, с
//             которого искать вхождение названия функции,
//             через который текущий элемент
//             будет (или нет) передвинут
// Возвращает: символ, обозначающий функцию согласно таблице:
//             s - sin(x)
//             c - cos(x)
//             t - tan(x)
//             g - ctg(x)
//             q - sqrt(x)
//             l - ln(x)
//             0 - не функция
char get_func(char **passback);

int write_number(char **passback, char **result, int pos);
int write_char(char ch, char **result, int pos);
int pop_and_write(node **stack, char **result, int pos);
int priority(char c);
int is_op(char c);
int is_func(char c);

#endif  // SRC_PARSE_MODULE_PARSER_H_
