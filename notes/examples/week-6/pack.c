#include <stdio.h>

typedef struct {
  unsigned short short1;
  int int1;
  unsigned char char1;
  int int2;

} foo_t;

foo_t foo;

main() {



  printf("foo        lives at %p\n", &foo);
  printf("foo.short1 lives at %p\n", &(foo.short1));
  printf("foo.int1   lives at %p\n", &(foo.int1));
  printf("foo.char1  lives at %p\n", &(foo.char1));
  printf("foo.int2   lives at %p\n", &(foo.int2));
  printf("sizeof(foo) = %d\n", sizeof(foo));

}
