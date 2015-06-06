/*
 * A C-Program to print the output generated
 * by a virtual direct-mapped cache
 *
 * Based on the io.c program by Peter C. Johnson
 */
#include "../virtual_cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define   HITCOST   1
#define   MISSCOST  50

int main(int argc, char *argv[]) {
  char *filename1, *filename2;
  filename1 = "-";
  filename2 = "-";
  FILE *fp1, *fp2;
  unsigned int n, count;
  char c;
  
  // If-string to work with file io from io.c
  if (argc > 2) {
    filename1 = argv[1];
    filename2 = argv[2];
  }
  
  if(strcmp(filename1, "-") == 0 || strcmp(filename2, "-") == 0) {
    fp1 = stdin;
    fp2 = stdin;
  } else {
    fp1 = fopen(filename1, "r");
    fp2 = fopen(filename2, "r");
    if(!fp1 || !fp2) {
      perror("fopen");
      exit(1);
    }
  }

  unsigned long int total_time1, total_time2;
  // Now use my virtual cache to simulate 2 2-Way set associative caches
  virtual_cache vc1, vc2;
  virtual_cache *vcp1, *vcp2;
  trace_counter tc1, tc2;
  trace_counter *tcp1, *tcp2;

  vcp1 = make_cache(2, 32);
  vcp2 = make_cache(2, 32);
  vc1 = *vcp1;
  vc2 = *vcp2;

  tcp1 = make_trace_counter();
  tcp2 = make_trace_counter();
  tc1 = *tcp1;
  tc2 = *tcp2;

  printf("\nversion = 1\n");
  
  count = 1;
  while(fscanf(fp1, "%c %x\n", &c, &n) != EOF) {
    parse_mem_req(&vc1, n, &tc1);
    count++;
  }
  printf("%d hits, %d misses, %d addresses\n", 
      tc1.hit_count, 
      tc1.miss_count,
      (count - 1));
  printf("Version1 Hit-rate: %f\n", (tc1.hit_count / (count - 1.0)));
  printf("Version1  Miss-rate: %f\n", (tc1.miss_count / (count - 1.0)));

  total_time1 = (tc1.hit_count * HITCOST) + (tc1.miss_count * MISSCOST);
  printf("Total time for version 1: %ld\n", total_time1);

  printf("\nversion = 2\n");

  count = 1;
  while(fscanf(fp2, "%c %x\n", &c, &n) != EOF) {
    parse_mem_req(&vc2, n, &tc2);
    count++;
  }

  printf("%d hits, %d misses, %d addresses\n",
      tc2.hit_count,
      tc2.miss_count,
      (count - 1));
  printf("Version2 hit-rate: %f\n", (tc2.hit_count / (count - 1.0)));
  printf("Version2 miss-rate: %f\n", (tc2.miss_count / (count - 1.0)));

  total_time2 = (tc2.hit_count * HITCOST) + (tc2.miss_count * MISSCOST);
  printf("Total time for version 2: %ld\n", total_time2);

  if (total_time2 > total_time1) {
    printf("\nVersion2 was %f times slower than Version1\n", ((float) total_time2 / (float) total_time1));
  } else {
    if (total_time1 > total_time2) {
      printf("\nVersion1 was %f times slower than Version2\n", ((float) total_time1 / (float) total_time2));
    }
    else {
      printf("Version1 and Version2 took the exact same amount of time!\n");
    }
  }

  free(tcp1);
  free(tcp2);
  free(vcp1);
  free(vcp2);
  fclose(fp1);
  fclose(fp2);
}
