/*
 * CS:APP Data Lab
 *
 * <Ryan Miyahara>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  /*Here we accumulate 1's in parallel (Thank you TA Yuchen) to search for any
  1's within x. We then return the inverse. If all bits are 0, this will make
  it return 1, but if there are any 1's, this will return 0.*/
  x = (x >> 16) | x;
  x = (x >> 8) | x;
  x = (x >> 4) | x;
  x = (x >> 2) | x;
  x = (x >> 1) | x;
  return ~x & 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  /*The approach for this problem is similar to the bitRepeat problem. We count the
  amount of 1's in each byte seperately, then gather the totals together. After
  that, we have to adjust the weighted totals since the positioning of the 1's
  will be off. My original method counted each bit, but went over the max
  operator limit.*/
  int sum = 0;
  int bit_mask_1a = 0x55 | (0x55 << 8);
  int bit_mask_1 = bit_mask_1a | (bit_mask_1a << 16);
  int bit_mask_2a = 0x33 | (0x33 << 8);
  int bit_mask_2 = bit_mask_2a | (bit_mask_2a << 16);
  int bit_mask_3a = 0x0F | (0x0F << 8);
  int bit_mask_3 = bit_mask_3a | (bit_mask_3a << 16);
  int final_count_a = 0xFF | (0xFF << 16);
  int final_count_b = 0xFF | (0xFF << 8);
  sum = (x & bit_mask_1) + ((x >> 1) & bit_mask_1);
  sum = (sum & bit_mask_2) + ((sum >> 2) & bit_mask_2);
  sum = (sum & bit_mask_3) + ((sum >> 4) & bit_mask_3);
  sum = (sum & final_count_a) + ((sum >> 8) & final_count_a);
  sum = (sum & final_count_b) + ((sum >> 16) & final_count_b);
  return sum;
}
/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  /*This algorithm finds the compliment of each argument. Using the & operator
  between these gives us what they don't have in common. Finding the compliment
  of this gives us what they do have in common.*/
  return ~(~x & ~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
  /*First we obtain the last n bits from x. Next we make a new variable and
  load the last n bits repetitively until n is full. Last, we return the new
  variable.*/
  int magik_mask = ~((-2) << (n - 1));
  int savthis = x & magik_mask;
  savthis = (savthis << (n % 32)) | savthis;
  savthis = ((savthis & ((!!((n << 1) /32)) -1)) << ((n << 1) % 32)) | savthis;
  savthis = ((savthis & ((!!((n << 2) /32)) -1)) << ((n << 2) % 32)) | savthis;
  savthis = ((savthis & ((!!((n << 3) /32)) -1)) << ((n << 3) % 32)) | savthis;
  return ((savthis & ((!!((n << 4) /32)) -1)) << ((n << 4) % 32)) | savthis;
  //11111111111111110110110110110110
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*The left side of this algorith (before the addition) accounts for uses a
  right shift to check if the numbers positive value will fit. The right side
  Checks if the number will fit into the bits if negative.*/
  return !(((~x & (x >> 31)) + (x & ~(x >> 31))) >> (n + ~0));
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /*Right shifting x to lose the lower bits by n puts the desired bytes in the
  lowest order position. (n is left shifted by 3 to account for hex and that
  each portion is 2 hex bytes.) We can then simply use the & to mask it to
  isolate the lowest order bits*/

  return (x >> (n << 3)) & 0xFF;
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*First, we need to check the signs of each argunent. We can do this by right
  shifting all the way, then masking the LSB. We can then subtract x and y and
  check the sign and overflow.*/
  int sign_x = (x >> 31) & 1;
  int sign_y = (y >> 31) & 1;
  int sign_sub = ((y + (~x + 1)) >> 31) & 1;

  return (!(sign_sub) & !(sign_x ^ sign_y)) | (sign_x & !sign_y);
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /*By right shifting by 31, we get the MSB. Normally, banging this would get
  the answer, but the zero case can be dealt with by double banging x. This
  does nothing for every answer, but returns 0 if x = 0.*/
  return (!(x >> 31) & !!x);
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  /*First, we create a bit mask consisting of n 0's on the left with the rest
  being 1's. Next we run that against x after arithmetically shifting it to
  the right. This will remove the 1's added on the left.*/

  int majik_mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & majik_mask;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*Left shift the int 1 to move it to the MSB, since all the other bytes will
  only add to the value, this is the most minimum value.*/

  int min = 1;
  return min << 31;
}
