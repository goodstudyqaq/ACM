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

int dest[6][2] = {1, 1, 0, 1, -1, 0, -1, -1, 0, -1, 1, 0};

void solve() {
    ll x, y;
    cin >> x >> y;
    vector<ll> c(6);
    for (int i = 0; i < 6; i++) {
        cin >> c[i];
    }
    if (x == 0 && y == 0) {
        cout << 0 << endl;
        return;
    }

    ll ans = numeric_limits<ll>::max() / 2;

    auto check = [&](int idx) -> ll {
        ll dx = dest[idx][0], dy = dest[idx][1];

        if (x * dy != y * dx) {
            return -1;
        } else {
            if (dx) {
                ll tmp = x / dx;
                if (tmp < 0) return -1;
                return tmp * c[idx];
            } else {
                ll tmp = y / dy;
                if (tmp < 0) return -1;
                return tmp * c[idx];
            }
        }
    };

    auto check2 = [&](int idx1, int idx2) -> ll {
        if (idx2 - idx1 == 3) return -1;
        ll dx1 = dest[idx1][0], dy1 = dest[idx1][1];
        ll dx2 = dest[idx2][0], dy2 = dest[idx2][1];
        if (dx1 == 0 || dx2 == 0) {
            if (dx1) {
                swap(dx1, dx2);
                swap(dy1, dy2);
                swap(idx1, idx2);
            }
            ll w2 = x / dx2;
            if (w2 < 0) return -1;
            ll tmp = y - dy2 * w2;
            ll w1 = tmp / dy1;
            if (w1 < 0) return -1;
            return c[idx1] * w1 + c[idx2] * w2;
        } else {
            if (dy1) {
                swap(dx1, dx2);
                swap(dy1, dy2);
                swap(idx1, idx2);
            }
            ll w2 = y / dy2;
            if (w2 < 0) return -1;
            ll tmp = x - dx2 * w2;
            ll w1 = tmp / dx1;
            if (w1 < 0) return -1;
            return c[idx1] * w1 + c[idx2] * w2;
        }
    };

    for (int i = 0; i < 6; i++) {
        ll tmp = check(i);
        if (tmp >= 0) {
            ans = min(ans, tmp);
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            ll tmp = check2(i, j);
            if (tmp >= 0) {
                ans = min(ans, tmp);
            }
        }
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