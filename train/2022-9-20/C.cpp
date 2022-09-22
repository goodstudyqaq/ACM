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
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    int lg = 32 - __builtin_clz(n);
    vector<vector<int>> val(lg);
    for (int i = 1; i <= n; i++) {
        val[31 - __builtin_clz(i)].push_back(i);
    }
    vector<int> color(n);

    function<void(int, int)> dfs = [&](int u, int pre) {
        for (auto v : V[u]) {
            if (v == pre) continue;
            color[v] = color[u] ^ 1;
            dfs(v, u);
        }
    };
    color[0] = 1;
    dfs(0, -1);
    debug(color);
    int w = accumulate(color.begin(), color.end(), 0);
    if (w > n - w) {
        w = n - w;
        for (int i = 0; i < n; i++) color[i] ^= 1;
    }

    vector<int> V2[2];
    for (int i = 0; i < n; i++) {
        V2[color[i]].push_back(i);
    }

    int idx1 = 0, idx2 = 0;
    vector<int> ans(n);
    // debug(lg);
    // debug(V2[0], V2[1]);
    // debug(val);
    for (int i = 0; i < lg; i++) {
        if ((w >> i) & 1) {
            int sz = val[i].size();
            for (int j = 0; j < sz; j++) {
                ans[V2[1][idx1++]] = val[i][j];
            }
        } else {
            int sz = val[i].size();
            for (int j = 0; j < sz; j++) {
                ans[V2[0][idx2++]] = val[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
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
}