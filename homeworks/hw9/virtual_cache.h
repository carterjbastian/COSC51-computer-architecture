/*
 * A Program that defines the necessary data types
 * and functions to simulate different types of
 * caches
 */

// Constants for the entire program
#define   BYTES_PER_BLOCK     16
#define   TOTAL_BLOCKS        64
#define   M                   32
#define   BUFFSIZE            100

// Header guard
#ifndef VIRTUAL_CACHE_H_INCLUDED
#define VIRTUAL_CACHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Definition of a cache_line data type
 * which stores a valid bit and a tag
 */
typedef struct { 
  unsigned char valid_bit;  //In a real cache this would be 1 bit
  unsigned int tag;         //The tag for said line
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
  int B; // Bytes per block
  cache_line *line_array;

  // Number of bits for each construct in memory access request
  int b_bits;
  int s_bits;
  int t_bits;

  // 32-bit masks for isolating tags and sets
  unsigned int tagmask;
  unsigned int setmask;

  // This will keep track of the least recently used line in each set
  int *LRU_line_array;

} virtual_cache;


/*
 * A Function to set all the cache lines' valid bit to 0 initially
 */
void initialize_cache_lines(cache_line *line_array, int number_of_lines) {
  int i;

  for (i = 0; i < number_of_lines; i++)
    line_array[0].valid_bit = 0;
}

/*
 * Function to generate a virtual cache object
 * and return a pointer to it based only on
 * e = number of lines per set and
 * s = number of sets
 */
virtual_cache * make_cache(int e, int s) {
  // Local vars used in making the masks
  int B_copy, S_copy, l;

  // Initialize it
  virtual_cache *vcp = malloc(sizeof(*vcp));
  vcp->E = e;
  vcp->S = s;
  vcp->B = BYTES_PER_BLOCK;

  // allocate memory for the array of unsigned ints that is line_array
  // We need enough space for the total number of lines in cache
  // (AKA E * S)
  vcp->line_array = malloc(sizeof(cache_line) * (vcp->E * vcp->S));

  // Don't want to destroy vcp's characteristics
  // so make local copies of the values
  B_copy = vcp->B;
  S_copy = vcp->S;
  l = 0;
  
  // Divide B by 2 until 0 (by bitshifting) => offset of b_bits
  while (B_copy >>= 1) {
    ++l;
  }
  vcp->b_bits = l;

  // Same process for S and s_bits
  l = 0;
  while (S_copy >>= 1) {
    ++l;
  }
  vcp->s_bits = l;
  // t_bits is the remainder of 32 - (number of other bits)
  vcp->t_bits = M - (vcp->b_bits + vcp->s_bits);

  initialize_cache_lines(vcp->line_array, (vcp->E * vcp->S));

  // Dynamically generate the tagmask and setmask
  // tagmask = bitstring of 1s only in the first t_bits
  vcp->tagmask = (0xffffffff << (M - vcp->t_bits));
  // setmask = funky. shift bitstring of 1s left s_bits, flip the bitstring
  // (so there are s_bits 1's in the least significant bits)
  // and then shift it left b_bits times to place the 1s in the correct
  // locations.
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

/*
 * A type that will count the hits and misses in a cache
 * as it goes through a memory trace
 */
typedef struct {
  unsigned int miss_count;
  unsigned int hit_count;
} trace_counter;

/*
 * Generates and returns a pointer to a trace counter
 */
trace_counter * make_trace_counter() {
  trace_counter *new_counter = malloc(sizeof(trace_counter));
  new_counter->miss_count = 0;
  new_counter->hit_count = 0;
  return new_counter;
}

/*
 * Function to parse a single memory request (using a virtual cache, a memory
 * request value, and a reference to a trace_counts).
 * Returns a string with the report on said memory request.
 * Also updates the trace counter and the virtual cache structures
 * to reflect the cache's processing of the memory request. 
 */
char * parse_mem_req(virtual_cache *vcp, unsigned int mem_req, trace_counter *tcp) {
  char *ret_val[BUFFSIZE];
  unsigned int set, tag;
  int set_start, set_stop, line_num, i, line_found, line_written;

  // Use set and tage masks to isolate the set and tag of the mem req.
  // Then find the addresses of the intended set's first and last lines
  // (in the virtual cache's line_array).
  set = (vcp->setmask & mem_req) >> vcp->b_bits;
  tag = (vcp->tagmask & mem_req);
  set_start = (set * vcp->E);
  set_stop = ((set+1) * vcp->E);

  // Look through each line in designated set for the requested data
  // record where it's found in line_found (or -1 otherwise).
  line_found = -1;
  line_num = 0;
  for (i = set_start + line_num; i < set_stop; (i = set_start + (++line_num))) {
    // In the cache line valid and marked with the right tag?
    if(vcp->line_array[i].valid_bit == 1 && vcp->line_array[i].tag == tag) {
      line_found = line_num;
    }
  }

  // Did we find the line?
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

        // Write the return value
        sprintf(ret_val,
            "addr 0x%08x; tag %x; looking in set %d; miss! line %d evicted, adding there\n",
            mem_req,
            (tag >> (M - vcp->t_bits)),
            (int) set,
            line_written);
        // This gets wonky 'cause ret_val is a variabl on the stack
        // So copy it into a string allocated in the heap before returning
        char * rstr = malloc((int) strlen(ret_val));
        strcpy(rstr, ret_val);
        tcp->miss_count++; // Update trace_counter object
        return rstr;
    }

    // We wrote it to an empty cache line, so return appropriately
    else {
      // Write the return string
      sprintf(ret_val,
          "addr 0x%08x; tag %x; looking in set %d; miss! line %d empty, adding there\n",
          mem_req,
          (tag >> (M - vcp->t_bits)),
          (int) set,
          line_written);
      // Allocate a string we can actually return
      char * rstr = malloc((int) strlen(ret_val));
      strcpy(rstr, ret_val);
      tcp->miss_count++; // Update trace counter
      return rstr;
    } 
  }
  else { //We found it, so return appropriately
    // Write the return string
    sprintf(ret_val, 
        "addr 0x%08x; tag %x; looking in set %d; found it in line %d; hit!\n",
        mem_req,
        (tag >> (M - vcp->t_bits)), 
        (int) set, 
        line_found);
    // Allocate memory for a string we can actually return
    char * rstr = malloc((int) strlen(ret_val));
    strcpy(rstr, ret_val);
    tcp->hit_count++; // Update the trace_counter
    return rstr;
  }
}
#endif
