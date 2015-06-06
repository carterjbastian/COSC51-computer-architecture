double data[MAXELEMS];

/*
 * Test - iterate over first elem elems of data
 * with stride of "stride"
 */
void test(int elems, int stride) {
  int i;
  double results = 0.0;
  volatile double sink;

  for (i = 0; i < elems; i += stride) {
    results += data[i];
  }

  sink = result; //So the compiler doesn't optimize away the loop
}

/*
 * run -  run test(elems, stride) and return the read throughput
 *        (MB/S). "size" is in bytes, "stride is in array elements
 *        and Mhz is CPU clock frequency in Mhz
 */
double run(int size, int stride, double Mhz) {
  double cycles;
  int elems = size / sizeof(double);

  test(elems, stride); //Warm up cache
  cycles = fcyc2(test, elems, stride, 0);
  return (size / stride) / (cycles / Mhz); // convert cycles to Mhz
}


