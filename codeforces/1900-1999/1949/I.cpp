#include <bits/stdc++.h>

#include <limits>

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

struct DSU {
    std::vector<int> f;
    DSU(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<long long> x(n), y(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }

    vector<vector<int>> V(n);
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long rsum = r[i] + r[j];
            long long dx = x[i] - x[j];
            long long dy = y[i] - y[j];

            if (dx * dx + dy * dy == rsum * rsum) {
                V[i].push_back(j);
                V[j].push_back(i);
                dsu.merge(i, j);
            }
        }
    }
    vector<int> color(n, -1);

    function<int(int, int, int)> dfs = [&](int u, int pre, int f) -> int {
        color[u] = f;
        int res = true;
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (color[v] != -1) {
                if (color[v] == f) {
                    return false;
                }
            } else {
                res &= dfs(v, u, f ^ 1);
            }
        }
        return res;
    };

    set<int> valid;
    for (int i = 0; i < n; i++) {
        valid.insert(dsu.leader(i));
    }

    vector<int> rm;
    for (auto it : valid) {
        bool res = dfs(it, -1, 0);
        if (res == false) {
            rm.push_back(it);
        }
    }

    for (auto r : rm) {
        valid.erase(r);
    }

    map<int, int> M;
    for (int i = 0; i < n; i++) {
        M[dsu.leader(i)] += (color[i] ? 1 : -1);
    }

    for (auto it : valid) {
        if (M[it] != 0) {
            debug(it, M[it]);
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
}