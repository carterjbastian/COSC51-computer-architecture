/*
 *
 * Program Name: 
 *
 * Program Description:
 *
 */

/* pre-processor directives */
#include <stdio.h>
#define STOP 0

/* Function     : main        */
/* Description  :             */
int main()
{
  /* variable Declarations */
  int counter;      /* descript */
  int startPoint;   /* descript */
  
  /* Prompt user for input */
  printf("===== Countdown Program =====\n");
  printf("Enter a positive integer: ");
  scanf("%d", &startPoint);

  /* Count down to zero */
  for (counter = startPoint; counter >= STOP; counter--)
    printf("%d\n", counter);
  
  /* Return */
  return 0;
}
