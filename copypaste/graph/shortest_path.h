#include <bits/stdc++.h>
using namespace std;

/*
套路题：二进制判不同色最短路。https://atcoder.jp/contests/abc245/tasks/abc245_g
*/

// 一般形式的 dijkstra
struct NormalDijkstra {
    // 下标从 1 到 n
    vector<vector<int>> Map;  // 图 Map[i][j] = dis
    vector<bool> vis;
    vector<int> d;
    const int inf = 0x3f3f3f3f;

    void dijkstra(int s, int n) {
        // O(n ^ 2)
        vis.clear(), vis.resize(n + 1, 0);
        d.clear(), d.resize(n + 1, inf);
        d[s] = 0;
        for (int i = 0; i < n; i++) {
            int x, m = inf;
            for (int y = 1; y <= n; y++) {
                if (!vis[y] && d[y] <= m) {
                    m = d[x = y];
                }
            }
            vis[x] = 1;
            for (int y = 1; y <= n; y++) {
                d[y] = min(d[y], d[x] + Map[x][y]);
            }
        }
    }
};

// 最短路
// 复杂度 O(mlogn) m <= n ^ 2, 适合稀疏图, 如果 m 很多则比普通的 dijkstra 更慢
namespace ShortestPath {
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
priority_queue<pli, vector<pli>, greater<pli>> Q;
vector<bool> vis;
vector<ll> dis;
const ll inf = numeric_limits<ll>::max() / 2;
void dijkstra(int n, vector<int>& valid, vector<vector<pii>>& V) {
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
