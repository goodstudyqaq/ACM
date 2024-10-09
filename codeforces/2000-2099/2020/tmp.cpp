#line 1 "D.cpp"
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
#line 4 "D.cpp"

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
    vector<UnionFind> uf(11, UnionFind(n + 1));

    while (m--) {
        int a, d, k;
        cin >> a >> d >> k;
        // [a, a + k * d]
        if (k == 0) continue;
        int r = a + (k - 1) * d;
        int now = uf[d].find(a);
        while (now <= r) {
            int go = now + d;
            uf[d].unite(now, go);
            now = uf[d].find(now);
        }
    }

    int group = 0;

    UnionFind uf2(n + 1);

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= n; j++) {
            uf2.unite(j, uf[i].find(j));
        }
    }

    set<int> S;
    for (int i = 1; i <= n; i++) {
        S.insert(uf2.find(i));
    }
    cout << S.size() << endl;
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
