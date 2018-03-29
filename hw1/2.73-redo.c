/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y)
{
  int TMax = 2147483647;
  int TMin = -2147483646;
  int sum = x + y;

  if (__builtin_add_overflow_p(int x, int y, (int) 0))
    return sum;

  if (x > 0 && y > 0)
    return TMax;
  else if (x < 0 && y < 0)
    return TMin;
  else
    return -1;
}
