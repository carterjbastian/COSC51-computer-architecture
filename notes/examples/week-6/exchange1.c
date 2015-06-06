int exchange(int *xp, int y) {
  int x = *xp; /* x is a local variable... */

  *xp = y;
  return x;
}
