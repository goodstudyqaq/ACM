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
    vector<pair<int, int>> V{{1, 1}, {2, 2}, {3, 3}, {-1, -1}};
    long long x = -1, y = 0;
    long long d[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

    auto get_mi_dis = [&]() {
        long long ans = 1e18;

        for (int i = 0; i < V.size(); i++) {
            ans = min(ans, abs(x - V[i].first) + abs(y - V[i].second));
        }
        return ans;
    };

    while (true) {
        int dir, k;
        cin >> dir >> k;

        x += d[dir][0] * k;
        y += d[dir][1] * k;
        long long ans = get_mi_dis();
        debug(x, y, ans);
    }
}