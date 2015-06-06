#include <stdio.h>
#include <unistd.h>

typedef struct {
  int field0;
  int field1;
  int field2;
} foo_t;


foo_t foo;



foo_t *fun3(foo_t fval) {

  fval.field0 =2;

  printf("fval lives at 0x%p\n", &fval);

  printf("fval.field0 = %d\n", fval.field0);

  return &fval;


}




int main() {

  int local;
  foo_t *foop;

  printf("main's local var lives at 0x%p\n", &local);



  printf("foo lives at 0x%p\n", &foo);

  foo.field0 = 0;

  printf("initially, foo.field0 equals %d\n", foo.field0);

  foop = fun3(foo);

  printf("after fun3, foop contains 0x%px\n", foop);

  printf("after fun3, foo.field0 equals %d\n", foo.field0);

  printf("dramatic pause...\n");
  sleep(5);

  printf("after fun3, foop->field0 equals %d\n", foop->field0);





}

