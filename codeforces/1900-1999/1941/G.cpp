#include <bits/stdc++.h>

#include <random>

#include "graph/graph-template.hpp"
#include "graph/shortest-path/dijkstra.hpp"

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

void solve() {
    int n, m;
    cin >> n >> m;

    Graph<> g(n);
    map<int, int> ID;
    int id = 0;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        if (ID.count(c) == 0) ID[c] = id++;
        c = ID[c];
        g.add_edge(u, v, c);
    }
    int color_num = id;
    debug(color_num);

    vector<int> belong(n);
    for (int i = 0; i < n; i++) {
        set<int> color;
        for (auto &e : g[i]) {
            color.insert(e.cost);
        }

        if (color.size() == 1) {
            belong[i] = *color.begin();
        } else {
            belong[i] = id++;
        }
    }
    debug(belong);

    debug(id);
    Graph<> g2(id);
    for (int i = 0; i < n; i++) {
        set<int> color;
        for (auto &e : g[i]) {
            color.insert(e.cost);
        }
        if (color.size() > 1) {
            for (auto &c : color) {
                g2.add_directed_edge(belong[i], c, 1);
                g2.add_directed_edge(c, belong[i], 0);
            }
        }
    }
    int b, e;
    cin >> b >> e;
    b--, e--;
    if (b == e) {
        cout << 0 << endl;
        return;
    }
    // debug(b, e);

    auto dist = dijkstra(g2, belong[b]).dist;
    // debug(dist);
    cout << dist[belong[e]] + (belong[b] < color_num) << endl;
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