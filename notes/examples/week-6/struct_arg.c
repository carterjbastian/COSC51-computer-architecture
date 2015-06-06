#include <stdio.h>
#include <unistd.h>

typedef struct {
  int field0;
  int field1;
  int field2;
} foo_t;


foo_t foo;

void fun1(foo_t *fp) {


  fp->field0 = 1;

  printf("fp->field0 lives at 0x%p\n", &(fp->field0));

  return;


}


void fun2(foo_t fval) {

  fval.field0 =2;

  printf("fval.field0 lives at 0x%p\n", &(fval.field0));

  return;


}



int main() {

  int local;

  printf("main's local var lives at 0x%p\n", &local);



  printf("foo.field0 lives at 0x%p\n", &(foo.field0));

  foo.field0 = 0;

  printf("initially, foo.field0 equals %d\n", foo.field0);

  fun1(&foo);

  printf("after fun1, foo.field0 equals %d\n", foo.field0);

  fun2(foo);

  printf("dramatic pause...\n");
  sleep(5);

  printf("after fun2, foo.field0 equals %d\n", foo.field0);



}

