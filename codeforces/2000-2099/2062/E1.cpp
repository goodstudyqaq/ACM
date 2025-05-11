#include <bits/stdc++.h>

#include "./structure/others/sparse-table.hpp"

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
    vector<int> w(n);
    vector<vector<int>> V(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<int> l(n), r(n);
    int t = 0;
    function<void(int, int)> dfs = [&](int u, int pre) {
        l[u] = t++;
        for (int v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
        }
        r[u] = t;
    };
    dfs(0, -1);
    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        int loc = l[i];
        val[loc] = w[i];
    }

    auto st = get_sparse_table(val, [&](int a, int b) {
        return max(a, b);
    });

    int find = -1;
    for (int i = 0; i < n; i++) {
        int _l = l[i], _r = r[i];
        int mx1 = w[i];

        int mx2 = 0;
        if (_l != 0) {
            mx2 = max(mx2, st.fold(0, _l));
        }
        if (_r != n) {
            mx2 = max(mx2, st.fold(_r, n));
        }
        if (mx2 > mx1) {
            if (find == -1 || w[find] < mx1) {
                find = i;
            }
        }
    }
    cout << find + 1 << '\n';
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