// sws, cs51, spring 2015
// -m32

#include <stdio.h>

int global = 123;

char c = 'a';

char *string="Green eggs and ham!";

int *gp = (int *)42;

char *cp = &c;

void subroutine(int x) {
  
  printf("a subroutine: address of x is %p\n", &x);
   	
}

int main() {

  printf("address of the subroutine is %p\n", &subroutine);
  subroutine(42);

  return 0;

}
