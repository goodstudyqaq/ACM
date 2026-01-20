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
typedef array<int, 2> a2;

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
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    if (n == 1) {
        cout << 0 << '\n';
        return;
    }
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            r[i] = x[1] - x[0];
        } else if (i == n - 1) {
            r[i] = x[n - 1] - x[n - 2];
        } else {
            int d1 = x[i] - x[i - 1];
            int d2 = x[i + 1] - x[i];
            r[i] = min(d1, d2);
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