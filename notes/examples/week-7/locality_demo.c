#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define  HALF   (1 << 14)

int main(void) {
  char *bigarray;
  unsigned int i, j, addr;
  int t1, t2; 
  float d_good, d_bad;
  clock_t clk;

  bigarray = malloc(HALF * HALF);
  if (bigarray == NULL) {
    printf("Malloc failed!\n");
    exit(-1);
  } else {
    printf("Allocated 0x%x by 0x%x bytes\n", HALF, HALF);
  }

  memset(bigarray, 0, HALF*HALF);

  printf("Looping i, then j\n");

  t1 = (int) (clk = clock());
  for(i = 0; i < HALF; i++) {
    for(j = 0; j < HALF; j++) {
      addr = (i * HALF) + j;
      bigarray[addr]++;
    }
  }
  t2 = (int) (clk = clock());
  printf("done!\n");

  d_good = ((t2 - t1) * 1000.0) / ((float) CLOCKS_PER_SEC);
  printf("Took %f milliseconds\n", d_good);

  printf("looping j, then i\n");

  t1 = (int) (clk = clock());
  for(j = 0; j < HALF; j++) {
    for(i = 0; i < HALF; i++) {
      addr = (i * HALF) + j;
      bigarray[addr]++;
    }
  }
  t2 = (int) (clk = clock());

  printf("Done!\n");
  d_bad = ((t2 - t1) * 1000.0) / ((float) CLOCKS_PER_SEC);
  printf("Took %f milliseconds\n", d_bad);

  printf("Bad took %f times longer!\n", (d_bad / d_good));
  return 0;
}
