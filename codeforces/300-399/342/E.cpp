#include <bits/stdc++.h>

#include "./graph/tree/heavy-light-decomposition.hpp"

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
    HeavyLightDecomposition<> g(n);
    g.read(n - 1);
    g.build();
    int len = sqrt(n * log(n) / log(2));
    typedef pair<int, int> pii;
    vector<pii> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
        queries[i].second--;
    }
    vector<int> dis(n);
    for (int i = 0; i < n; i++) {
        dis[i] = g.dep[i];
    }

    for (int i = 0; i < q; i += len) {
        int r = min(q, i + len);
        // [i, r)
        vector<int> red;
        for (int j = i; j < r; j++) {
            if (queries[j].first == 1) {
                red.push_back(queries[j].second);
            } else {
                int v = queries[j].second;
                int ans = dis[v];
                for (auto u : red) {
                    ans = min(ans, g.dist(u, v));
                }
                cout << ans << '\n';
            }
        }

        queue<int> Q;

        for (int j = i; j < r; j++) {
            if (queries[j].first == 1) {
                dis[queries[j].second] = 0;
                Q.push(queries[j].second);
            }
        }
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (auto v : g[u]) {
                if (dis[v] > dis[u] + 1) {
                    dis[v] = dis[u] + 1;
                    Q.push(v);
                }
            }
        }
    }
}