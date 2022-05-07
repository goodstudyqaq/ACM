#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    if (n <= 2) {
        cout << 2 << endl;
        return;
    }
    if (n <= 6) {
        cout << 3 << endl;
        return;
    }

    ll l = 1, r = 1e9;
    ll ans = -1;

    auto get_val = [&](ll val) -> ll {
        ll tmp1 = val / 3;
        ll res = tmp1 * 6;
        ll res2 = tmp1 * (tmp1 - 1) * 2 * 3;
        if (val % 3 == 1) {
            res += 2 * tmp1 * 2;
        } else if (val % 3 == 2) {
            res += (val - tmp1 - 1) * 2 + tmp1 * 2;
        }
        return res + res2;
    };

    auto check = [&](ll val) -> bool {
        ll res = get_val(val);
        return res >= n;
    };

    while (l <= r) {
        ll mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    debug(get_val(ans));
    debug(get_val(ans - 1));

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