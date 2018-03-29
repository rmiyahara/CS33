/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y)
{
  int TMax = 2147483647;
  int TMin = -2147483646;
  int bitmask = 1 << ((sizeof(x) << 3) - 1);
  int x_mask = x & bitmask;
  int y_mask = y & bitmask;
  int sum_mask = (x + y) & bitmask;
  int max_flag = ~x_mask & ~y_mask & sum_mask;
  int min_flag = x_mask & y_mask & !sum_mask;

  int sum;
  (max_flag) && (sum = TMax);
  (min_flag) && (sum = TMin);

  return sum;
}
