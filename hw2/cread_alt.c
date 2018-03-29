long cread_alt(long *xp) {
  long result = 0;
  long *x3 = &result;
  if (xp)
    x3 = xp;
  return *x3;
}
/*This implementation works because it tests the xp pointer's address rather
than its value. Line 4 converts the address to a bool. If the address is null,
this statement will return false and x3 will continue to point at the value 0.
If true it will change the value x3 points to to xp's value.*/
