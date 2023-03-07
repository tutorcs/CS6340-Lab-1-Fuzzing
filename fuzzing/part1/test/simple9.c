https://tutorcs.com
WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <stdio.h>

int main() {
  int i, a = 0, b = fgetc(stdin);
  for (i = 10000; i > 0; i--)
    printf("%d\n", b * b / (i - b)); // Divide by zero
  return 0;
}
