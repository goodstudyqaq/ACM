#include <bits/stdc++.h>

#include <limits>

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

    vector<vector<int>> V(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
    }
    for (int i = 1; i < n; i++) {
        V[i].push_back(i + 1);
    }

    vector<int> res(n + 1);
    res[1] = 1;

    int inf = numeric_limits<int>::max() / 2;
    vector<int> d(n + 1, inf);
    d[1] = 0;
    int mx = 0;
    for (int i = 2; i <= n; i++) {
        for (int v : V[i - 1]) {
            if (d[v] > d[i - 1] + 1) {
                d[v] = d[i - 1] + 1;
                mx = max(mx, v - d[v]);
            }
        }
        // debug(i, mx);

        if (i >= mx) {
            res[i] = 1;
        } else {
            res[i] = 0;
        }
    }
    for (int i = 1; i < n; i++) {
        cout << res[i];
    }
    cout << endl;
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