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
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<bool> vis(a[n] + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            vis[a[i] / j] = 1;
        }
    }

    int ans = 1e5;
    for (int i = 1; i <= a[1]; i++) {
        if (vis[i] == 0) continue;
        int r = i;
        for (int j = 1; j <= n; j++) {
            int val = a[j];
            int p = a[j] / i;
            p = min(p, k);
            r = max(r, a[j] / p);
        }
        ans = min(ans, r - i);
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