#include <stdio.h>
#include <string.h>


/* byte_pointer is a pointer to an unsigned character */
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
  int i;
  for (i = 0; i < len; i++)
    printf(" %.2x", start[i]);
  printf("\n");
}

/* typecasts a pointer to an int to a pointer to an unsigned char */
void show_int(int x) {
  show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
  show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
  show_bytes((byte_pointer) &x, sizeof(void *));
}

int main() {
  int i = 1;
  float f = 1.0;
  void *xp = &i;
  void *yp = &f;

  printf("i is: ");
  show_int(i);
  printf("f is: ");
  show_float(f);

  printf("xp is: ");
  show_pointer(xp);
  printf("yp is: ");
  show_pointer(yp);

  const char *s = "abcdef";
  printf("String = %s, length = %d\n", s, strlen(s));
  show_bytes((byte_pointer) s, strlen(s));

  return 0;
}
