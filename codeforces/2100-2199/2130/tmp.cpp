#line 1 "C.cpp"
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
#line 4 "C.cpp"

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
    UnionFind uf(2 * n + 1);

    vector<int> a(n), b(n);
    vector<int> vis(n);
    int sz = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];

        if (uf.same(a[i], b[i])) {
            continue;
        }
        vis[i] = 1;
        sz++;
        uf.unite(a[i], b[i]);
    }
    cout << sz << '\n';
    // set<pii> S;
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            // S.insert({a[i], b[i]});
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';

    // int l = 0, r = 0;
    // // [l, r)
    // int ans = 0;
    // for (auto it : S) {
    //     if (it.first <= r) {
    //         r = max(r, it.second);
    //     } else {
    //         ans += r - l;
    //         l = it.first;
    //         r = it.second;
    //     }
    // }
    // ans += r - l;
    // cout << ans << '\n';
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
