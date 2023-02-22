#ifndef SRC_IO_MODULE_IO_MODULE_H_
#define SRC_IO_MODULE_IO_MODULE_H_
#define WIDTH 80
#define HEIGHT 25

//   Получает: на вход указатель на строку (массив символов)
// Возвращает: результат считывания(1 - успешно, 2 - неудачно)
int input(char **str);

// Печатает график
void print_graph(const double *values);

void values_fill(char *rpn_exp, double *values);
#endif  // SRC_IO_MODULE_IO_MODULE_H_
