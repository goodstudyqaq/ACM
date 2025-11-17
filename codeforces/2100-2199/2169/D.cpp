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

void solve() {
    long long x, y, k;
    cin >> x >> y >> k;

    // 每次去掉 y, 2y ...

    if (k < y) {
        cout << k << '\n';
        return;
    }

    long long l = 1, r = 1e12;

    auto check = [&](long long val) -> pll {
        bool ok = false;
        for (int i = 0; i < x; i++) {
            if (val < y) break;
            if (val % y == 0) {
                ok = true;
            }
            val -= val / y;
        }
        return {val, ok};
    };

    while (l <= r) {
        ll mid = l + r >> 1;
        pll ans = check(mid);
        // debug(l, r, mid, ans);
        if (ans.second == 1) {
            if (ans.first < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        } else {
            if (ans.first == k) {
                cout << mid << '\n';
                return;
            } else if (ans.first < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    cout << -1 << '\n';
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