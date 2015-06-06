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


int main(int argc, char *argv[]) {
  char *filename = "-";
  FILE *fp;
  unsigned int n, count;
  char c;
  
  // If-string to work with file io from io.c
  if (argc > 1)
    filename = argv[1];
  
  if(strcmp(filename, "-") == 0) {
    fp = stdin;
  } else {
    fp = fopen(filename, "r");
    if(!fp) {
      perror("fopen");
      exit(1);
    }
  }

  // Now use my virtual cache to simulate a direct mapped cache for q1
  virtual_cache vc;
  virtual_cache *vcp;
  trace_counter tc;
  trace_counter *tcp;

  vcp = make_cache(64, 1);
  vc = *vcp;

  tcp = make_trace_counter();
  tc = *tcp;

  printf("\nmode = fully associative\n");
  
  count = 1;
  while(fscanf(fp, "%c %x\n", &c, &n) != EOF) {
    parse_mem_req(&vc, n, &tc);
    count++;
  }
  printf("%d hits, %d misses, %d addresses\n", 
      tc.hit_count, 
      tc.miss_count,
      (count - 1));
  printf("Direct Mapped Hit-rate: %f\n", (tc.hit_count / (count - 1.0)));
  printf("Direct Mapped Miss-rate: %f\n", (tc.miss_count / (count - 1.0)));

  free(tcp);
  free(vcp);
  fclose(fp);
}
