#include <stdio.h>
#include <stdlib.h>

/* 
 * Function: main
 * 
 * Description: writes a .hex file of exactly 1kb
 * of the ASCII encoding of the lyrics to "Never
 * Gonna Give You Up" by Rick Astley
 *
 */
int main() {
  /* Variable Declarations */
  FILE *in;
  FILE *out;

  int byte_count;
  int c;

  /* open files */
  in = fopen("impt_data.txt", "r");
  out = fopen("impt_data.hex", "a");

  /* Set up the .hex file */
  fprintf(out, "v2.0 raw\n");
  

  /* The loop that does the work */
  for (byte_count = 0; byte_count < 1024; byte_count += 4) {
    /* Get a character from Rick */
    c = fgetc(in);
    if ( feof(in) ) {
      rewind(in);
      c = fgetc(in);
    }
    
    /* Print binary of that character to out */
    fprintf(out, "%.2x 00 00 00\n", c);

  }

  /* Close the files! */
  fclose(in);
  fclose(out);

  return 0;
}
