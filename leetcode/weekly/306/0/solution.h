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
    vector<vector<int>> largestLocal(vector<vector<int>>& g) {
        int n = g.size();
        int m = g[0].size();

        vector<vector<int>> res(n - 2, vector<int>(m - 2));
        for (int i = 0; i < n - 2; i++) {
            for (int j = 0; j < m - 2; j++) {
                int it = 0;
                for (int k = i; k < i + 3; k++) {
                    for (int t = j; t < j + 3; t++) {
                        it = max(it, g[k][t]);
                    }
                }
                res[i][j] = it;
            }
        }
        return res;
    }
};