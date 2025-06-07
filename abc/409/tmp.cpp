#line 1 "F.cpp"
#include <bits/stdc++.h>

#line 4 "F.cpp"

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
#line 6 "F.cpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    typedef pair<int, int> pii;
    vector<pii> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
    }

    typedef array<int, 3> a3;
    priority_queue<a3, vector<a3>, greater<>> Q;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int d = abs(p[i].first - p[j].first) + abs(p[i].second - p[j].second);
            Q.push({d, i, j});
        }
    }

    vector<a3> query(q);
    int cnt = n;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        query[i][0] = t;
        if (t != 2) {
            cin >> query[i][1] >> query[i][2];
        }
        if (t == 1) {
            cnt++;
        }
    }

    UnionFind uf(cnt);

    for (int i = 0; i < q; i++) {
        int t = query[i][0];
        if (t == 1) {
            int a = query[i][1], b = query[i][2];
            for (int i = 0; i < n; i++) {
                int d = abs(p[i].first - a) + abs(p[i].second - b);
                Q.push({d, n, i});
            }
            p.push_back({a, b});
            n++;
        } else if (t == 2) {
            while (!Q.empty()) {
                auto [d, u, v] = Q.top();
                if (!uf.same(u, v)) {
                    break;
                }
                Q.pop();
            }

            if (Q.empty()) {
                cout << -1 << '\n';
                continue;
            }

            auto [d, u, v] = Q.top();
            while (!Q.empty()) {
                auto [d2, u2, v2] = Q.top();
                if (d == d2) {
                    uf.unite(u2, v2);
                    Q.pop();
                } else {
                    break;
                }
            }
            cout << d << '\n';

        } else {
            int u = query[i][1], v = query[i][2];
            u--, v--;
            if (uf.same(u, v)) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
}
