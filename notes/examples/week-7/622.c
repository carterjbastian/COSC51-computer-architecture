// Example adopted from 6.22 in the textbook
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define   N   (1 << 18)

typedef struct {
  int vel[3];
  int acc[3];
} point;

point p[N];

// Function converts a pointer to a timeval structure (sys/time.h)
// to micro seconds 
long tv_to_usecs(struct timeval *tvp) {
  long secs, usecs;
  secs = tvp->tv_sec;
  usecs = tvp->tv_usec;
  return ( (secs * 1000 * 1000) + usecs);

}

// Function accepts two pointers to timeval
// structures (from sys/time.h) and returns
// The difference between the two in microseconds 
long tvdiff(struct timeval *tvp1, struct timeval *tvp2) {
  long t1, t2;

  t1 = tv_to_usecs(tvp1);
  t2 = tv_to_usecs(tvp2);

  return (t2 - t1);
}

// Clear function - version 1
// Prediction: Best! stride-1
void clear1(point *p, int n) {
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < 3; j++)
      p[i].vel[j] = 0;
    for (j = 0; j < 3; j++)
      p[i].acc[j] = 0;
  }
}

// Clear function - version 2
// Prediction: Medium! stride-3
void clear2(point *p, int n) {
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < 3; j++) {
      p[i].vel[j] = 0;
      p[i].acc[j] = 0;
    }
  }
}

/* Clear function - version 3
 * Prediction: Worse! stride-n
 */
void clear3(point *p, int n) {
  int i, j;

  for (j = 0; j < 3; j++) {
    for (i = 0; i < n; i++)
      p[i].vel[j] = 0;
    for (i = 0; i <n; i++)
      p[i].acc[j] = 0;
  }
}

/* Main! */
int main(int argc, char *argv[]) {

  struct rusage start, stop;
  long utime, stime, ttime;

  int option;

  // Make sure usage is correct
  if (argc < 2) {
    printf("Usage: %s n\n", argv[0]);
    exit(-1);
  }
  
  option = atoi(argv[1]);

  printf("clear%d \n", option);

  //Start timing
  if (-1 == getrusage(RUSAGE_SELF, &start)) {
    printf("error getting start time \n");
    exit(-1);
  }

  switch(atoi(argv[1])) {
    case 1:
      clear1(p, N);
      break;
    case 2:
      clear2(p, N);
      break;
    case 3:
      clear3(p, N);
      break;
    default:
      printf("Not an option!\n");
      exit(-1);
  }

  // stop timing
  if (-1 == getrusage(RUSAGE_SELF, &stop)) {
    printf("error getting stop time \n");
    exit(-1);
  }

  utime     = tvdiff(&start.ru_utime, &stop.ru_utime);
  stime     = tvdiff(&start.ru_stime, &stop.ru_stime);
  ttime     = utime + stime;

  printf("Microseconds: %ld\n", ttime);

  printf("done!\n");

  int i = atoi(argv[1]);

  /* if (i < 3) {
      i++;
      char *argsnext[i];
      argsnext[0] = argv[0];
      char stri[15];
      sprintf(stri, "%d", i);
      argsnext[1] = stri;
      main(2, argsnext);
  }
  */
}
