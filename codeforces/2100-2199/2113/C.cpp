#include <bits/stdc++.h>

#include "./dp/cumulative-sum-2d.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> mp(n);
    for (int i = 0; i < n; i++) {
        cin >> mp[i];
    }

    CumulativeSum2D<int> sum(n, m);
    int all = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mp[i][j] == 'g') {
                all++;
                sum.add(i, j, 1);
            }
        }
    }

    sum.build();
    debug(sum.query(0, 0, n - 1, m - 1));

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mp[i][j] == '.') {
                int x1 = max(i - k + 1, 0);
                int y1 = max(j - k + 1, 0);
                int x2 = min(i + k - 1, n - 1);
                int y2 = min(j + k - 1, m - 1);
                int tmp = sum.query(x1, y1, x2, y2);
                // debug(i, j, x1, y1, x2, y2, tmp);
                ans = max(ans, all - tmp);
            }
        }
    }
    cout << ans << '\n';
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}