/* Question 2 from HW7 */
#include <stdio.h>

/* Globals */
unsigned char monthB = 1;
unsigned char monthA = 1;
unsigned char dayB = 3;
unsigned char dayA = 1;

unsigned int output;

// Sets the output global to the error indicator
void error_out() {
  output = 0xe;
  return;
}

// Converts the two month input values to a decimal month value
int get_month(unsigned char mB, unsigned char mA) {
  if ((int) mB >= 10 || (int) mA >= 10) {
    error_out();
    return -1; // indicate error
  }
  return ((((int) mB) * 10) + ((int) mA));
}

// Converts the two day input values to a decimal day value
int get_day(unsigned char dB, unsigned char dA) {
  if ((int) dB >= 10 || (int) dA >= 10) {
    error_out();
    return -1; // Indicate error
  }
  return (((int) dB) * 10) + ((int) dA);
}

/* Function that returns the correct output value
 * for any given decimal month and day values
 */
int check_day(int m, int d) {
  if (m == 0 || d == 0) {
    return 0;
  }
  if (m > 12 || d > 31) {
    return 0;
  }

  /* Check for each month */
  switch(m) {
    /* Jan */
    case 1 :
      return (d <= 31);
      break;
    
    /* Feb */
    case 2 :
      return (d <= 28);
      break;

    /* March */
    case 3 :
      return (d <= 31);
      break;

    /* April */
    case 4 :
      return (d <= 30);
      break;

    /* May */
    case 5 :
      return (d <= 31);
      break;

    /* June */
    case 6 :
      return (d <= 30);
      break;

    /* July */
    case 7 :
      return (d <= 31);
      break;

    /* August */
    case 8 :
      return (d <= 31);
      break;

    /* September */
    case 9 :
      return (d <= 30);
      break;

    /* October */
    case 10 :
      return (d <= 31);
      break;

    /* November */
    case 11 :
      return (d <= 30);
      break;

    /* December */
    case 12:
      return (d <= 31);
      break;
    
    /* Default */
    default :
      return 0;
  }

  return 0xe;
}

/*
 * main method checks if the input given by the 4 global
 * inputs represents a date in the 2015 calendar, sets
 * the output appropriately, and prints both the 
 * date encoded and the output value to the console
 */
int main() {
  int month;
  int day;

  month = get_month(monthB, monthA);
  day = get_day(dayB, dayA);

  // Handle error cases
  if (month == -1 || day == -1) {
    printf("Month, Day: (%d, %d)\n", month, day);
    printf("Output: %x\n", output);
    return 1;
  }
  // Otherwise, handle correct cases
  output = check_day(month, day);
  printf("Month, Day: (%d, %d)\n", month, day);
  printf("Output: %x\n", output);

  return 0;
}


