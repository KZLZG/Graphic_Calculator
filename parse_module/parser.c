#include "parser.h"

char get_func(char **passback) {
  // Константы строк операций
  const char sin_string[] = "sin";
  const char cos_string[] = "cos";
  const char tan_string[] = "tan";
  const char ctg_string[] = "ctg";
  const char sqrt_string[] = "sqrt";
  const char ln_string[] = "ln";
  // ---------

  char *from = *passback;
  char result = 0;
  char bracket_consumer;
  char buffer[5] = "----";
  int i = 0;

  while (*from != '\0' && i < 4 && *from > 96 && *from < 123) {
    buffer[i++] = *from;
    from++;
  }
  bracket_consumer = *from;
  buffer[i] = '\0';

  if (bracket_consumer == '(') {
    if (i == 3) {
      if (strcmp(buffer, sin_string) == 0) {
        result = 's';
      } else if (strcmp(buffer, cos_string) == 0) {
        result = 'c';
      } else if (strcmp(buffer, tan_string) == 0) {
        result = 't';
      } else if (strcmp(buffer, ctg_string) == 0) {
        result = 'g';
      }
      *passback = *passback + 3;
    }
    if (i == 2 && strcmp(buffer, ln_string) == 0) {
      result = 'l';
      *passback = *passback + 2;
    }
    if (i == 4 && strcmp(buffer, sqrt_string) == 0) {
      result = 'q';
      *passback = *passback + 4;
    }
  }

  return result;
}

int write_number(char **passback, char **result, int pos) {
  char *current = *passback;
  while (*current && ((*current > 47 && *current < 58) || *current == '.')) {
    *result = realloc(*result, (pos + 1) * sizeof(char));
    *(*result + pos++) = *current;
    current++;
  }
  *result = realloc(*result, (pos + 1) * sizeof(char));
  *(*result + pos++) = ' ';
  *passback = current;
  return pos;
}

int write_char(char ch, char **result, int pos) {
  *result = realloc(*result, (pos + 2) * sizeof(char));
  *(*result + pos++) = ch;
  *(*result + pos++) = ' ';
  return pos;
}

int pop_and_write(struct node **stack, char **result, int pos) {
  char_lf popped;
  *stack = pop(*stack, &popped);
  return write_char(popped.ch, result, pos);
}

int priority(char c) {
  return c == '~' || c == 's' || c == 'c' || c == 't' || c == 'g' || c == 'q' ||
                 c == 'l'
             ? 5
         : c == '^'             ? 4
         : c == '*' || c == '/' ? 3
         : c == '+' || c == '-' ? 2
                                : 0;
}

int is_op(char c) {
  return c == '~' || c == '*' || c == '/' || c == '+' || c == '-' || c == '^'
             ? 1
             : 0;
}

int is_func(char c) {
  return c == 's' || c == 'c' || c == 't' || c == 'g' || c == 'q' || c == 'l'
             ? 1
             : 0;
}

int exp_to_rpn(char *expression, char **result) {
  int status = 1;  // результат парсинга
  int pos = 0;  // текущая позиция записи в строке RPN
  int next_can_be_unary = 1;
  char_lf to_push;
  struct node *stack = NULL;
  char *current = expression;

  while (*current && status) {
    if (*current > 47 && *current < 58) {
      pos = write_number(&current, result, pos);
      next_can_be_unary = 0;
    } else {
      char func_ch = get_func(&current);
      if (func_ch) {
        to_push.ch = func_ch;
        stack = push(stack, to_push);
      } else {
        if (is_op(*current)) {
          if (*current == '-' && next_can_be_unary) *current = '~';
          next_can_be_unary = 1;
          while (stack && is_op(stack->data.ch) &&
                 (*current == '~'
                      ? priority(stack->data.ch) > priority(*current)
                      : priority(stack->data.ch) >= priority(*current))) {
            pos = pop_and_write(&stack, result, pos);
          }
          to_push.ch = *current;
          stack = push(stack, to_push);
        } else {
          if (*current == '(') {
            next_can_be_unary = 1;
            to_push.ch = *current;
            stack = push(stack, to_push);
          } else if (*current == ')') {
            next_can_be_unary = 0;
            while (stack && stack->data.ch != '(') {
              pos = pop_and_write(&stack, result, pos);
            }
            if (!stack) {
              status = 0;  // mismatched parenthesis
            } else {
              char_lf trash_can;
              stack = pop(stack, &trash_can);
              if (stack && is_func(stack->data.ch))
                pos = pop_and_write(&stack, result, pos);
            }
          } else if (*current == 'x') {
            next_can_be_unary = 0;
            pos = write_char(*current, result, pos);
          } else {
            if (*current != ' ') status = 0;  // illegal characters
          }
        }
        current++;
      }
    }
  }
  while (stack && status) {
    if (stack->data.ch == '(' || stack->data.ch == ')')
      status = 0;  // mismatched parenthesis
    pos = pop_and_write(&stack, result, pos);
  }
  write_char('\0', result, pos);
  destroy(stack);
  return status;
}
