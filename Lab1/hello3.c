#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  char s[100];
  int i;
  int n;
  srand(time(0));
  n = rand() % 11;
  printf("n is %d\n", n);
  printf("Enter your name: ");
  scanf("%99s", s);

  for (i = 0; i < n; i++) {
    if (n % 2 == 0) {
      printf("hello, %s!\n", s);
    }
    else {
      printf("hi there, %s!\n", s);
    }
  }
  return 0;
}
