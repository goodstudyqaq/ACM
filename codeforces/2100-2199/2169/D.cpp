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
    for (int i = 0; i < x; i++) {
        k += (k - 1) / (y - 1);
        if (k > limit) {
            cout << -1 << '\n';
            return;
        }
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