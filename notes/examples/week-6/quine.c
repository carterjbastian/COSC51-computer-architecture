// sws, cs51, spring 2015
// -m32

#include <stdio.h>

#define LINELEN 16

void aftermain(void);

int main(void) {

  int i;
  unsigned char *cp;
  unsigned char *start = (unsigned char *) &main;
  unsigned char *end = (unsigned char *) &aftermain;


  for (cp = start; cp < end; cp += LINELEN)  {

    printf("%p: ", cp);
    for (i = 0; i < LINELEN; i++)
      printf(" %02x ", *(cp+i));
    printf("\n");
  }

  return 0;

}

void aftermain(void){

}
