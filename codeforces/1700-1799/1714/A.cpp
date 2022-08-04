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
    int n, H, W;
    cin >> n >> H >> W;
    vector<int> h(n), w(n), t(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i] >> w[i];
        t[i] = h[i] * 60 + w[i];
    }
    sort(t.begin(), t.end());
    int T = H * 60 + W;
    auto idx = lower_bound(t.begin(), t.end(), T) - t.begin();
    debug(idx);
    int res;
    if (idx == n) {
        res = 24 * 60 - T + t[0];
    } else {
        res = t[idx] - T;
    }

    cout << res / 60 << ' ' << res % 60 << endl;
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