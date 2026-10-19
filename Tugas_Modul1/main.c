#include <stdio.h>

int fibonacci(int n) {
  if(n == 0) {
    return 0;
  } else if(n == 1) {
    return 1;
  }

  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  double a = 3.6;
  double b = 3;

  int c = -20;
  int d = -3;

  // printf("%d", c % d);
  printf("%d", fibonacci(5));
  return 0;
}
