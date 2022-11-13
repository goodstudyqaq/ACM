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
    long long makeIntegerBeautiful(long long n, int target) {
        vector<int> V;
        long long x = n;
        int sum = 0;
        while (x) {
            V.push_back(x % 10);
            x /= 10;
        }
        sum = accumulate(V.begin(), V.end(), 0);
        if (sum <= target) {
            return 0;
        }

        long long res = n;
        for (int i = 0; i < V.size(); i++) {
            sum -= V[i];
            res /= 10;
            if (sum + 1 <= target) {
                res++;
                for (int j = 0; j <= i; j++) {
                    res *= 10;
                }
                return res - n;
            }
        }
        res++;

        for (int j = 0; j < V.size(); j++) {
            res *= 10;
        }
        return res - n;
    }
};