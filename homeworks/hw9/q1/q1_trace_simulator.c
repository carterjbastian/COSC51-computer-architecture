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

  // CHANGE THE FOLLOWING LINE TO CHANGE TYPE OF CACHE MODEL
  vcp = make_cache(64, 1);
  vc = *vcp;

  tcp = make_trace_counter();
  tc = *tcp;

  // Start output
  printf("\ntagmask = 0x%08x\n", vc.tagmask);
  printf("setmask = 0x%08x\n", vc.setmask);
  // CHANGE THIS LINE TO REFLECT THE TYPE OF CACHE MODEL
  printf("mode = fully associative\n");
  printf("%d blocks, %d bytes in block, %d sets, %d line per set\n",
      TOTAL_BLOCKS,
      BYTES_PER_BLOCK,
      vc.S,
      vc.E);
  
  count = 1;
  while(fscanf(fp, "%c %x\n", &c, &n) != EOF) {
    printf("%d: %s", count, parse_mem_req(&vc, n, &tc));
    count++;
  }
  printf("%d hits, %d misses, %d addresses\n", 
      tc.hit_count, 
      tc.miss_count,
      (count - 1));
  free(vcp);
  free(tcp);
  fclose(fp);

}
