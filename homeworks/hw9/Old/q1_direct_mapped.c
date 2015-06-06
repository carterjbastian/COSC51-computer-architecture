/*
 * A C-Program to print the output generated
 * by a virtual direct-mapped cache
 *
 * Based on the io.c program by Peter C. Johnson
 */
#include "virtual_cache.h"
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
  virtual_cache direct_vc;
  virtual_cache *direct_vcp;
  trace_counter direct_tc;
  trace_counter *direct_tcp;

  direct_vcp = make_cache(2, 32);
  direct_vc = *direct_vcp;

  direct_tcp = make_trace_counter();
  direct_tc = *direct_tcp;

  // Start output
  printf("tagmask = 0x%08x\n", direct_vc.tagmask);
  printf("setmask = 0x%08x\n", direct_vc.setmask);
  printf("mode = direct mapped\n");
  printf("%d blocks, %d bytes in block, %d sets, %d line per set\n",
      TOTAL_BLOCKS,
      BYTES_PER_BLOCK,
      direct_vc.S,
      direct_vc.E);
  
  count = 1;
  while(fscanf(fp, "%c %x\n", &c, &n) != EOF) {
    printf("%d: %s", count, parse_mem_req(&direct_vc, n, &direct_tc));
    count++;
  }
  printf("%d hits, %d misses, %d addresses\n", 
      direct_tc.hit_count, 
      direct_tc.miss_count,
      (count - 1));
}
