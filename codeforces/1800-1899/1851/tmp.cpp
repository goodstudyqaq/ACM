#line 1 "G.cpp"
#include <bits/stdc++.h>

#line 3 "/Users/guoshen/code/library2/structure/union-find/union-find.hpp"

using namespace std;

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
#line 4 "G.cpp"

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
    vector<int> h(n);
    typedef array<int, 5> event;
    vector<event> events;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        events.push_back({h[i], 0, i});
    }

    vector<vector<int>> V(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b, e;
        cin >> a >> b >> e;
        a--, b--;
        events.push_back({h[a] + e, 1, a, b, i});
    }

    sort(events.begin(), events.end());

    vector<bool> ans(q);
    UnionFind uf(n);
    vector<bool> vis(n);

    for (auto &e : events) {
        if (e[1] == 0) {
            vis[e[2]] = 1;
            for (auto v : V[e[2]]) {
                if (vis[v]) {
                    uf.unite(e[2], v);
                }
            }
        } else {
            ans[e[4]] = (uf.find(e[2]) == uf.find(e[3]));
        }
    }

    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
    debug("end");
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
