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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    function<bool(int L, int R, int l, int r)> check = [&](int L, int R, int l, int r) -> bool {
        if (r - l == 0) {
            return true;
        }
        // 区间 [l, r] 的值的范围为 [L, R]
        int m = l + r >> 1;
        int mv = L + R >> 1;
        int f = 0;
        for (int i = l; i <= m; i++) {
            f += (a[i] <= mv);
        }

        if (f != 0 && f != (m - l + 1)) {
            return false;
        }
        if (f == 0) {
            ans++;
            return check(mv + 1, R, l, m) & check(L, mv, m + 1, r);
        } else {
            return check(L, mv, l, m) & check(mv + 1, R, m + 1, r);
        }
    };

    if (!check(1, n, 1, n)) {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;
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
}