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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<long long> ans(n);

    function<void(int, int, int, long long, long long, long long)> dfs = [&](int u, int pre, int d, long long sum, long long mx, long long mi) {
        if (d % 2 == 0) {
            sum += a[u];
            mi = min(mi, sum);
            mx = max(mx, sum);
            ans[u] = sum - mi;
        } else {
            sum -= a[u];
            mi = min(mi, sum);
            mx = max(mx, sum);
            ans[u] = -(sum - mx);
        }

        for (auto v : V[u]) {
            if (v == pre) {
                continue;
            }
            dfs(v, u, d + 1, sum, mx, mi);
        }
    };
    dfs(0, -1, 0, 0, 0, 0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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