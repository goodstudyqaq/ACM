#include <bits/stdc++.h>

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

map<array<int, 4>, int> dp;
int query(int l1, int r1, int l2, int r2, int Len) {
    if (l1 == 0 && r1 == Len && l2 == 0 && r2 == Len) {
        return 1;
    }
    if (dp.count({l1, r1, l2, r2})) {
        return dp[{l1, r1, l2, r2}];
    }
    int m = Len / 2;

    int res = 0;
    if (l1 < m && l2 < m) {
        res += query(l1, min(m, r1), l2, min(m, r2), m);
    }
    if (l1 < m && r2 > m) {
        res += query(l1, min(m, r1), max(l2, m) - m, r2 - m, m);
    }
    if (r1 > m && l2 < m) {
        res += query(max(m, l1) - m, r1 - m, l2, min(m, r2), m);
    }
    if (r1 > m && r2 > m) {
        res += query(max(m, l1) - m, r1 - m, max(l2, m) - m, r2 - m, m);
    }
    return dp[{l1, r1, l2, r2}] = res;
}

void solve() {
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;

    cout << query(l1, r1, l2, r2, 1 << 20) << '\n';
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