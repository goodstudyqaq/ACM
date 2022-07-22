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
    vector<int> a(n), loc(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        loc[a[i]] = i;
    }

    int l = loc[0], r = loc[0];
    int ans = 1;
    const int mod = 1e9 + 7;

    for (int i = 1; i < n; i++) {
        int idx = loc[i];
        if (l <= idx && idx <= r) {
            // 随便找一个地方放
            ans = 1LL * ans * (r - l + 1 - i) % mod;
        } else {
            l = min(l, idx);
            r = max(r, idx);
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