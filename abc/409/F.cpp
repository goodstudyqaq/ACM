#include <bits/stdc++.h>

#include <queue>

#include "./structure/union-find/union-find.hpp"

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