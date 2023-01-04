/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

class Solution {
   public:
    int smallestValue(int n) {
        while (true) {
            int s = n;
            int sum = 0;
            for (int i = 2; i * i <= s; i++) {
                if (s % i == 0) {
                    while (s % i == 0) {
                        sum += i;
                        s /= i;
                    }
                }
            }
            if (s != 1) {
                sum += s;
            }
            if (sum == n) break;
            n = sum;
        }
        return n;
    }
};