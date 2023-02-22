#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void console_input();
int check_path(char *mas);
int input(char **str);



int main() {
  console_input();
  return 0;
}

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



void console_input() {
    int enter_num = 1, f_is_opened = 1;
    char c;
    char *mas;

    while (enter_num == 1 && f_is_opened == 1) {
        enter_num = 0;
        scanf("%d%c", &enter_num, &c);
        if (c == '\n' && enter_num == 1) {
                if (input(&mas)) {
                    f_is_opened = check_path(mas);
                    printf("\n");
                }
        } else if (enter_num == -1) {
                enter_num = 0;
        } else {
            enter_num = 0;
            printf("n/a");
        }
    }
}



int check_path(char *mas) {
    FILE *fp;
    //  int flag = 1;
    if ((fp = fopen(mas, "r")) == NULL) {
        printf("n/a");
        // flag = 0;

    } else {
        char s[100];
        while (fgets(s, 100, fp))
            printf("%s", s);
    }
    return 1;
}

