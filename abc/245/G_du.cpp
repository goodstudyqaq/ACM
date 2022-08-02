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
typedef pair<ll, int> pli;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

// 最短路
namespace ShortestPath {
priority_queue<pli, vector<pli>, greater<pli>> Q;
vector<bool> vis;
vector<ll> dis;
const ll inf = numeric_limits<ll>::max() / 2;
void dijkstra(int n, vector<int> &valid, vector<vector<pii>> &V) {
    vis.resize(n + 1);
    dis.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        vis[i] = 0;
        dis[i] = inf;
    }
    while (!Q.empty()) Q.pop();

    for (auto it : valid) {
        dis[it] = 0;
        Q.push({dis[it], it});
    }

    while (!Q.empty()) {
        auto it = Q.top();
        Q.pop();
        if (vis[it.second]) continue;
        vis[it.second] = true;
        for (auto v : V[it.second]) {
            if (dis[v.first] > it.first + v.second) {
                dis[v.first] = it.first + v.second;
                Q.push({dis[v.first], v.first});
            }
        }
    }
}
}  // namespace ShortestPath

vector<vector<pii>> V;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m, k, l;
    cin >> n >> m >> k >> l;
    vector<int> a(n + 1), b(l + 1);
    V.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= l; i++) {
        cin >> b[i];
    }

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        V[u].push_back({v, c});
        V[v].push_back({u, c});
    }

    vector<ll> ans(n + 1, ShortestPath::inf);

    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 2; j++) {
            vector<int> valid;
            for (int k = 1; k <= l; k++) {
                int idx = b[k];
                if (((a[idx] >> i) & 1) == j) {
                    valid.emplace_back(idx);
                }
            }
            ShortestPath::dijkstra(n, valid, V);

            for (int k = 1; k <= n; k++) {
                if (((a[k] >> i) & 1) != j) {
                    ans[k] = min(ans[k], ShortestPath::dis[k]);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i] == ShortestPath::inf) ans[i] = -1;
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}