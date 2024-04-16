#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    int n, q;
    cin >> n >> q;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> V(n + 1);
    vector<int> fa(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        fa[i] = p;
        V[p].push_back(i);
    }
    vector<int> sz(n + 1);
    vector<int> dep(n + 1);
    vector<int> IDX(n + 1);
    function<void(int, int)> dfs = [&](int u, int d) {
        IDX[u] = sz[d];
        sz[d]++;
        dep[u] = d;
        for (auto v : V[u]) {
            dfs(v, d + 1);
        }
    };

    dfs(1, 0);

    int LIMIT = sqrt(n);
    vector<vector<long long>> res(n + 1, vector<long long>(LIMIT, -1));

    function<long long(int, int)> ask = [&](int x, int y) -> long long {
        if (x == 0 && y == 0) return 0;
        int d = dep[x];
        if (x > y) swap(x, y);

        int y_idx = IDX[y];

        if (sz[d] <= LIMIT && res[x][y_idx] != -1) return res[x][y_idx];

        long long ans = ask(fa[x], fa[y]) + a[x] * a[y];
        if (sz[d] <= LIMIT) {
            res[x][y_idx] = ans;
        }
        return ans;
    };

    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << ask(x, y) << endl;
    }
}
