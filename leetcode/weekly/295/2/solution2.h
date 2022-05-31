#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

class Solution {
   public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> stk;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            int mx = 0;
            while (stk.size() && stk.back().first <= nums[i]) {
                mx = max(mx, stk.back().second);
                stk.pop_back();
            }
            if (stk.size())
                mx++;
            else
                mx = 0;
            ans = max(ans, mx);
            stk.push_back({nums[i], mx});
        }
        return ans;
    }
};
