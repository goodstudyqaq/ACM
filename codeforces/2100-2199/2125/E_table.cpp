#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int n = 3;
    int x = 10;
    vector<int> v(3);
    int res = 0;

    auto check = [&]() {
        int sum = 0;
        
    };

    function<void(int d, int num)> dfs = [&](int d, int num) {
        if (d == 3) {
            if (check()) {
                res++;
            }
            return;
        }
        for (int i = num; i <= x; i++) {
            v[d] = i;
            dfs(d + 1, i + 1);
        }
    };

    dfs(0, 1);
};
