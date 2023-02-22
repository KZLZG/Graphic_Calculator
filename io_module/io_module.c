#include "io_module.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../calc_module/calc_module.h"

int input(char **str) {
  int status = 1;
  int k = 1;
  char current = -1;
  while (scanf("%c", &current) && current != '\n' && current != EOF) {
    *str = realloc(*str, k * sizeof(char));
    *(*str + (k - 1)) = current;
    k++;
  }
  if (k == 1) status = 0;
  *str = realloc(*str, k * sizeof(char));
  *(*str + (k - 1)) = '\0';
  return status;
}

void print_graph(const double *values) {
  // double graph_y = -100.0;
  double graph_y = -1.0;
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      // if ((100 * values[x] >= graph_y) && (100 * values[x]) < graph_y + 8)
      //   printf("*");
      // else
      //   printf(".");
      if ((graph_y - values[x] < 1e-15) &&
          (values[x] - (graph_y + 0.08) < 1e-15))
        printf("*");
      else
        printf(".");
    }
    printf("\n");
    graph_y += 0.08;
  }

  // graph_y += 8;
}

// функция заполнения переданного массива(с индексами по Х) значений У
// Получает: на вход указатель на пустой массив и выражение
void values_fill(char *rpn_exp, double *values) {
  for (int x = 0; x < WIDTH; x++) {
    char *temp_rpn = malloc(strlen(rpn_exp) * sizeof(char));
    temp_rpn = strcpy(temp_rpn, rpn_exp);
    double graph_x = 0 + ((4 * M_PI) / (WIDTH - 1)) * x;
    values[x] = calc(temp_rpn, graph_x);
    free(temp_rpn);
  }
}
