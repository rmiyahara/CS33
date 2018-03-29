int int_shifts_are_arithmetic()
{
  int check = 149;
  if ((check >> 4) == 9) {
    return 0;
  }
  else if ((check >> 4) == 249) {
    return 1;
  }
  else { //You should never get here.
    return 0;
  }
}
