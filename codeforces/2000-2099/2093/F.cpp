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
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    vector<vector<string>> b(m, vector<string>(n));
    vector<int> same(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<bool> ok(n);
    int mx_idx = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
            if (b[i][j] == a[j]) {
                same[i]++;
                ok[j] = 1;
            }
        }
        if (same[i] > same[mx_idx]) {
            mx_idx = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!ok[i]) {
            cout << -1 << '\n';
            return;
        }
    }
    int ans = n + (n - same[mx_idx]) * 2;
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