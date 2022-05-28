#include<stdio.h>
#include<stdbool.h>
// Get all palindromic digits in octal
// x: from 0 to Inf, if x is a palindromic digits in octal, it will be printed.
// y: A copy of x's the second half
// z: A copy of x's the first half
// p: Check if y and z are equal
main(x, y, z, p) {
    while (y=++x) {
        // At first y is a copy of x, after that, y will be divided into two part.
        z = 0;
        while (z < y) {
            z = z * 8 + y % 8;
            y /= 8;
        }
        // Check the two part are equal.
        p = ((z == y) | ((z / 8) == y));
        if (!p) continue;
        printf("%o\n", x);
    }
}