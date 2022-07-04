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
    int ans, k;
    vector<int> V;
    vector<int> num;
    void dfs(int idx) {
        if (idx == V.size()) {
            int tmp = *max_element(num.begin(), num.end());
            ans = min(ans, tmp);
            return;
        }

        for (int i = 0; i < k; i++) {
            num[i] += V[idx];
            dfs(idx + 1);
            num[i] -= V[idx];
        }
    }

    int distributeCookies(vector<int>& _V, int _k) {
        num.resize(_k);
        for (int i = 0; i < _k; i++) {
            num[i] = 0;
        }
        V = _V;
        k = _k;
        int n = V.size();
        ans = 1e9;
        dfs(0);
        return ans;
    }
};