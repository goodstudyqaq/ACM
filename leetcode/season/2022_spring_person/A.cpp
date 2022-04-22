#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

class Solution {
   public:
    int giveGem(vector<int>& gem, vector<vector<int>>& op) {
        int n = gem.size();
        int m = op.size();
        for (int i = 0; i < m; i++) {
            int tmp = gem[op[i][0]] / 2;
            gem[op[i][0]] -= tmp;
            gem[op[i][1]] += tmp;
        }
        sort(gem.begin(), gem.end());
        return gem[n - 1] - gem[0];
    }
};
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
}