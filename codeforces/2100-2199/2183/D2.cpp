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
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<vector<int>> V2(n);
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        V2[d].push_back(u);
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    };
    dfs(0, -1, 0);
    int ans = 1;

    for (int i = 0; i < n; i++) {
        if (V2[i].size() == 0) break;
        int sz1 = V2[i].size();
        ans = max(ans, sz1);

        if (i + 1 < V2.size()) {
            int sz2 = V2[i + 1].size();
            if (sz1 > sz2) {
                continue;
            }
            // sz1 < sz2
            int cnt = 0;
            for (auto u : V2[i]) {
                int szu = V[u].size();

                if (u != 0) szu--;
                if (szu > 0) cnt++;

            }
            debug(i, sz1, sz2, cnt);

            if (cnt > 1) continue;

            // 只有 1 个
            ans = max(ans, sz2 + 1);
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