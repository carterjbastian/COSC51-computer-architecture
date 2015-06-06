#include <stdio.h>

int global = 123;
char c = 'a';
char *string = "Green eggs and ham!";
int *gp = &global;
char *cp = &c;

int main() {
  printf("global is at: %x\n", gp); 
  return 0;
}
