// sws, cs51
#include <stdio.h>

int x;

int main() {
  
  x = 0x7FFFFFFF;

  printf("x = %d (hex 0x%x)\n", x ,x);

  x = x + 1;

  printf("x = %d\n", x);

}
