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

struct DSU2 {
    std::vector<int> f;
    DSU2(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
};
typedef array<int, 3> a3;

void solve() {
    int n, m;
    cin >> n >> m;
    string ans(m, '0');
    vector<a3> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges[i] = {u, v, i};
    }
    int one = m - (n - 1);
    debug(one);
    if (one < 3) {
        vector<a3> left;
        DSU2 dsu(n);
        for (int i = 0; i < m; i++) {
            auto [u, v, idx] = edges[i];
            if (!dsu.merge(u, v)) {
                left.push_back(edges[i]);
            }
        }
        debug(left);
        for (int i = 0; i < left.size(); i++) {
            ans[left[i][2]] = '1';
        }
        cout << ans << endl;
    } else {
        vector<a3> left;
        DSU2 dsu(n);
        for (int i = 0; i < m; i++) {
            auto [u, v, idx] = edges[i];
            if (!dsu.merge(u, v)) {
                left.push_back(edges[i]);
            }
        }
        dsu = DSU2(n);

        auto check = [&]() {
            map<int, int> M;
            for (auto it : left) {
                M[it[0]]++;
                M[it[1]]++;
            }
            if (M.size() != 3) return true;
            for (auto it : M) {
                if (it.second != 2) return true;
            }
            return false;
        };

        if (check()) {
            for (auto it : left) {
                ans[it[2]] = '1';
            }
        } else {
            int c_idx = left[0][2];
            dsu.merge(left[0][0], left[0][1]);
            left.clear();
            for (int i = 0; i < m; i++) {
                auto [u, v, idx] = edges[i];
                if (idx == c_idx) continue;
                if (!dsu.merge(u, v)) {
                    ans[idx] = '1';
                }
            }
        }

        cout << ans << endl;
    }
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