#include <bits/stdc++.h>

#include "graph/shortest-path/dijkstra.hpp"

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

    int n, m;
    cin >> n >> m;
    Graph<long long> g(n);
    g.read(m, -1, true, false);

    auto sp = dijkstra(g, 0);

    long long ans = sp.dist[n - 1];
    const long long inf = numeric_limits<long long>::max();
    if (ans == inf) {
        cout << -1 << '\n';
    } else {
        int now = n - 1;
        vector<int> res;
        while (now) {
            res.push_back(now);
            now = sp.from[now];
        }

        reverse(res.begin(), res.end());
        cout << 1;
        for (auto v : res) {
            cout << " " << v + 1;
        }
        cout << '\n';
    }
}