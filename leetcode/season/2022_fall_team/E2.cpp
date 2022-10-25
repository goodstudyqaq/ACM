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
    vector<vector<int>> ans;
    void work(int size, int offset_x, int offset_y) {
        auto push = [&](int x, int y) {
            ans.push_back({x + offset_x, y + offset_x});
        };
        push(1, 1);
        for (int i = 2; i <= size; i++) {
            push(i, 1);
            if (i != 2) {
                // 不放 (2, 3)
                push(i, 2 * i - 1);
            }
        }

        if (size <= 3) {
            // 只放两边
            if (size >= 2) {
                push(2, 3);
            }
            return;
        }

        push(4, 4);
        if (size == 4) {
            return;
        }
        work(size - 4, offset_x + 4, offset_y + 4);
    }

    vector<vector<int>> sandyLandManagement(int size) {
        ans.clear();
        work(size, 0, 0);
        return ans;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
    freopen("./data.out", "w", stdout);
#endif
    Solution s;
    auto res = s.sandyLandManagement(1000);
}