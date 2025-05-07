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
    int n;
    cin >> n;
    vector<vector<int>> V(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    map<int, int> cnt;
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) -> void {
        int sz = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            sz++;
            dfs(v, u, d + 1);
        }
        if (sz == 0) cnt[d]++;
    };
    int ans = 0;
    for (auto v : V[1]) {
        cnt.clear();
        dfs(v, 1, 0);
        int mx = 0;
        debug(cnt, v);

        for (auto it : cnt) {
            if (mx >= it.first) {
                mx += it.second;
            } else {
                mx = it.first + it.second;
            }
        }

        ans = max(ans, mx);
    }
    cout << ans << '\n';
}