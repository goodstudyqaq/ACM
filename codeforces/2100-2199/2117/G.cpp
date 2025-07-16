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

struct UnionFind {
    vector<int> data;
    vector<int> f;

    UnionFind() = default;

    explicit UnionFind(size_t sz) : data(sz, 1), f(sz) {
        iota(f.begin(), f.end(), 0);
    }

    bool unite(int x, int y) {  // x merge to y
        x = find(x), y = find(y);
        if (x == y) return false;
        data[y] += data[x];
        f[x] = y;
        return true;
    }
    int find(int x) {
        if (f[x] == x) return x;
        int y = find(f[x]);
        data[y] += data[x];
        f[x] = y;
        return f[x];
    }
    int size(int x) {
        return data[find(x)];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    vector<vector<int>> groups() {
        int n = (int)data.size();
        vector<vector<int>> ans(n);
        for (int i = 0; i < n; i++) {
            ans[find(i)].push_back(i);
        }

        ans.erase(remove_if(ans.begin(), ans.end(), [&](const vector<int>& v) {
                      return v.empty();
                  }),
                  ans.end());
        return ans;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    typedef array<int, 3> a3;
    vector<a3> edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }
    sort(edges.begin(), edges.end());
    UnionFind uf(n + 1);
    vector<int> data(n + 1, 1e9 + 1);
    int now = 0;
    debug(edges);
    int ans = edges[0][0] + edges[m - 1][0];
    debug(ans);
    while (now < m) {
        auto [w, u, v] = edges[now];
        int fu = uf.find(u);
        int fv = uf.find(v);
        if (fu != fv) {
            uf.f[fv] = fu;
            data[fu] = min(data[fu], data[fv]);
            data[fu] = min(data[fu], w);
        }
        if (uf.same(1, n)) {
            int f = uf.find(1);
            ans = min(ans, data[f] + w);
        }
        now++;
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