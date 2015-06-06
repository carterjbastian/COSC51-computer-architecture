#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * A Program that defines the necessary data types
 * and functions to simulate different types of
 * caches
 */
#define   BYTES_PER_BLOCK     16
#define   TOTAL_BLOCKS        64
#define   M                   32
#define   BUFFSIZE            100

/*
 * Definition of a cache_line data type
 * which stores a valid bit and a tag
 */
typedef struct { 
  unsigned char valid_bit;
  unsigned int tag;
  // In real cache, we would have 16-bit block here  
} cache_line;

/*
 * Definition of a virtual_cache data type
 * which stores info about the cache such as
 * the number of lines in each set, number
 * of sets total, number of blocks per
 * set, a pointer to the line array,
 * and info for memory address parsing
 */
typedef struct {
  int E; // Number of Lines per Set
  int S; // Number of sets in cache
  int B;
  cache_line *line_array;

  int b_bits;
  int s_bits;
  int t_bits;

  unsigned int tagmask;
  unsigned int setmask;

  int *LRU_line_array;

} virtual_cache;


void initialize_cache_lines(cache_line *line_array, int number_of_lines) {
  int i;

  for (i = 0; i < number_of_lines; i++)
    line_array[0].valid_bit = 0;
}

virtual_cache * make_cache(int e, int s) {
  int B_copy, S_copy, l; // for finding log2

  virtual_cache *vcp = malloc(sizeof(*vcp));
  vcp->E = e;
  vcp->S = s;
  vcp->B = BYTES_PER_BLOCK;
  // allocate memory for the array of unsigned ints that is line_array
  // We need enough space for the total number of lines in cache
  // (AKA E * S)
  vcp->line_array = malloc(sizeof(cache_line) * (vcp->E * vcp->S));

  B_copy = vcp->B;
  S_copy = vcp->S;
  l = 0;
  
  while (B_copy >>= 1) {
    ++l;
  }
  vcp->b_bits = l;

  l = 0;
  while (S_copy >>= 1) {
    ++l;
  }
  vcp->s_bits = l;
  vcp->t_bits = M - (vcp->b_bits + vcp->s_bits);

  initialize_cache_lines(vcp->line_array, (vcp->E * vcp->S));

  vcp->tagmask = (0xffffffff << (M - vcp->t_bits));
  vcp->setmask = (~(0xffffffff << (vcp->s_bits)) << vcp->b_bits);

  // Set up the LRU_line_array
  // An array where int a index i
  // is the line number of the least recently
  // used line in set i.
  vcp->LRU_line_array = malloc(sizeof(int) * vcp->S); // Need an elem for each set
  // Initialize all vals to 0
  for (int i = 0; i < vcp->S; i++) {
    vcp->LRU_line_array[i] = 0;
  }
  
  return vcp;
}


char * parse_mem_req(virtual_cache *vcp, unsigned int mem_req) {
  char *ret_val[BUFFSIZE];
  unsigned int set, tag;
  int set_start, set_stop, line_num, i, line_found, line_written, line_evict;

  set = (vcp->setmask & mem_req) >> vcp->b_bits;
  tag = (vcp->tagmask & mem_req);
  set_start = (set * vcp->E);
  set_stop = ((set+1) * vcp->E);

  // Look through each line in designated set for the requested data
  // record where it's found in line_found (or -1 otherwise).
  line_found = -1;
  line_num = 0;
  for (i = set_start + line_num; i < set_stop; (i = set_start + (++line_num))) {
    if(vcp->line_array[i].valid_bit == 1 && vcp->line_array[i].tag == tag) {
      line_found = line_num;
    }
  }


  if (line_found == -1) {
    // If line wasn't found, look through the cache for an empty line in the set
    line_written = -1;
    line_num = 0;
    for (i = set_start + line_num; i < set_stop; (i = set_start + (++line_num))) {
      // We found an emtpy line! Add the info here
      if (vcp->line_array[i].valid_bit == 0) {
        vcp->line_array[i].valid_bit = 1;
        vcp->line_array[i].tag = tag;
        line_written = line_num;
        break; // Stop looping through
      }
    }

    // If empty line wasn't found, evict Least Recently Written Line
    // and write it there. Return as such.
    if (line_written == -1) {
        line_written = vcp->LRU_line_array[set]; // Get line to evict
        vcp->LRU_line_array[set] = ((line_written + 1) % vcp->E); // Update LRU val

        vcp->line_array[set_start + line_written].tag = tag; // Update cache line

        sprintf(ret_val,
            "addr 0x%08x; tag %x; looking in set %d; miss! line %d evicted, adding there\n",
            mem_req,
            (tag >> (M - vcp->t_bits)),
            (int) set,
            line_written);
        char * rstr = malloc((int) strlen(ret_val));
        strcpy(rstr, ret_val);
        return rstr;
    }

    // We wrote it to an empty cache line, so return appropriately
    else {       
      sprintf(ret_val,
          "addr 0x%08x; tag %x; looking in set %d; miss! line %d empty, adding there\n",
          mem_req,
          (tag >> (M - vcp->t_bits)),
          (int) set,
          line_written);
      char * rstr = malloc((int) strlen(ret_val));
      strcpy(rstr, ret_val);
      return rstr;
    } 
  }
  else { //We found it, so return appropriately
    sprintf(ret_val, 
        "addr 0x%08x; tag %x; looking in set %d; found it in line %d; hit!\n",
        mem_req,
        (tag >> (M - vcp->t_bits)), 
        (int) set, 
        line_found);
    char * rstr = malloc((int) strlen(ret_val));
    strcpy(rstr, ret_val);
    return rstr;
  }
}

/*
 * Main for testing that these utilities work
 */
int main() {
  virtual_cache my_vc;
  virtual_cache *vp;

  vp = make_cache(1, 64); // direct mapped cache
  my_vc = *vp;

  printf("Cache Lines per set: %d\n",  my_vc.E);
  printf("Cache number of sets: %d\n", my_vc.S);
  printf("Cache bytes per block: %d\n", my_vc.B);
  printf("sizeof virtual cache: %d\n", (int) sizeof(virtual_cache));
  printf("size of my_vc: %d\n", (int) sizeof(my_vc));
  printf("sizeof cache_line: %d\n", (int) sizeof(cache_line));
  printf("s: %d\n", my_vc.s_bits);
  printf("b: %d\n", my_vc.b_bits);
  printf("t: %d\n", my_vc.t_bits);
  printf("Cache line 0 valid bit: %d\n", my_vc.line_array[0].valid_bit);
  printf("Last Cache Line valid bit: %d\n", my_vc.line_array[my_vc.S * my_vc.E - 1].valid_bit);
  printf("Direct mapped tagmask: 0x%08x\n", my_vc.tagmask);
  printf("Direct mapped setmask: 0x%08x\n", my_vc.setmask);

  unsigned int test_mem_req = 0x22222210;
  printf("Test mem_req results: %s", parse_mem_req(&my_vc, test_mem_req));
  printf("%s", parse_mem_req(&my_vc, 0x33333310));
  printf("%s", parse_mem_req(&my_vc, 0x44444410));
  printf("%s", parse_mem_req(&my_vc, 0x55555510));
  printf("%s", parse_mem_req(&my_vc, 0x66666610));
  printf("%s", parse_mem_req(&my_vc, 0x22222210));
  printf("%s", parse_mem_req(&my_vc, 0x33333310));
  printf("%s", parse_mem_req(&my_vc, 0x8fe01030));
  printf("%s", parse_mem_req(&my_vc, 0x8fe01031));
  printf("%s", parse_mem_req(&my_vc, 0xbffff8fc));

  //printf("size of my_vc's line_array: %d\n", (int) sizeof(*(my_vc.line_array)));
  //printf("vp: %p\n", vp);
  //printf("Value of vp: %d\n", *vp);
  //printf("vp + sizeof(int): %p\n", (vp + 1));
  //printf("Value of vp + sizeof(int): %d\n", *(vp + 1));
}
