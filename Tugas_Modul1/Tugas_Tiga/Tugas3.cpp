#include <cstdio>
#include <iostream>
#include <cmath>
#define PI 3.1415926535
int main() {
  double L1, L2, tetha1, tetha2;
  double x, y;
  
  L1 = 10;  
  L2 = 5;
  tetha1 = 30 * PI / 180;
  tetha2 = 10 * PI / 180;

  x = (L1 * cos(tetha1)) + (L2 * cos(tetha1 + tetha2));
  y = (L1 * sin(tetha1)) + (L2 * sin(tetha1 + tetha2));
  
  printf("%lf", sin(tetha1));
  printf("Titik akhir untuk sumbu x adalah : %.2lf\n", x);
  printf("Titik akhir untuk sumbu y adalah : %.2lf\n", y);
  return 0;
}
