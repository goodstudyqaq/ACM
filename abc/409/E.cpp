#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    typedef pair<int, int> pii;
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<pii>> V(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        V[u].push_back({v, w});
        V[v].push_back({u, w});
    }

    long long ans = 0;
    function<void(int, int, int)> dfs = [&](int u, int pre, int w) {
        for (auto v : V[u]) {
            if (v.first == pre) continue;
            dfs(v.first, u, v.second);
        }
        int val = a[u];
        if (val != 0) {
            a[pre] += 1LL * val;
            ans += 1LL * abs(val) * w;
        }
    };
    dfs(0, -1, 0);
    cout << ans << '\n';
}