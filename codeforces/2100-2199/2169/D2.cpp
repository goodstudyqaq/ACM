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

    if (y == 1) {
        cout << -1 << '\n';
        return;
    }

    const ll limit = 1e12;

    while (x) {
        ll jump = (k - 1) / (y - 1);
        if (jump == 0) break;
        ll r = ((k - 1) / (y - 1) + 1) * (y - 1);

        ll dis = r - k;

        ll tmp = dis / jump + 1;

        ll mi = min(tmp, x);
        x -= mi;

        if (k > limit - jump * mi) {
            cout << -1 << '\n';
            return;
        }
        k += jump * mi;
    }

    cout << k << '\n';
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