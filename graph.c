#include <math.h>
#include <stdio.h>

#include "calc_module/calc_module.h"
#include "io_module/io_module.h"
#include "parse_module/parser.h"

void run_calc();

int main() {
  run_calc();
  return 0;
}

void run_calc() {
  char *mas = NULL;
  char *res = NULL;

  if (input(&mas)) {
    int parse_status = exp_to_rpn(mas, &res);
    if (parse_status) {
      double values[WIDTH];
      values_fill(res, values);
      print_graph(values);
    } else {
      printf("Parse error!\n");
    }
  } else {
    printf("Input error");
  }
  if (res) free(res);
  if (mas) free(mas);
}
