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
    int mi = a[1];
    vector<vector<int>> f(a[n] + 1);
    for (int i = 1; i <= n; i++) {
        f[a[i]].push_back(i);
    }
    int mx = a[n];
    int ans = mx - mi;

    for (int i = mx; i >= 0; i--) {
        if (f[i].size()) {
            ans = min(ans, i - mi);
            for (auto idx : f[i]) {
                if (i == (a[idx] / k)) {
                    cout << ans << endl;
                    return;
                }
                int val = a[idx] / (a[idx] / i + 1);
                mi = min(mi, val);
                f[val].push_back(idx);
            }
        }
        vector<int>().swap(f[i]);
    }
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