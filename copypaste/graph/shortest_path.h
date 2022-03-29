#include <bits/stdc++.h>
using namespace std;

namespace ShortestPath {
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

struct VectorDijkstra {
    // 复杂度 O(mlogn) m <= n ^ 2, 适合稀疏图, 如果 m 很多则比普通的 dijkstra 更慢
    // 链式前向星
    struct Edge {
        int u, v, nxt;
        // 其他信息 如权重等。。
        int w;
        // extra_info
    };
    vector<Edge> edges;
    vector<int> head;
    int ecnt;

    struct HeapNode {
        int d, u;
        bool operator<(const HeapNode& rhs) const {
            return d > rhs.d;
        }
    };
    vector<bool> done;
    vector<int> d;
    const int inf = 0x3f3f3f3f;
    void dijkstra(int s, int n) {
        priority_queue<HeapNode> Q;
        d.clear(), d.resize(n + 1, inf);
        d[s] = 0;
        done.clear(), done.resize(n + 1, 0);
        Q.push((HeapNode){0, s});
        while (!Q.empty()) {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if (done[u]) continue;
            done[u] = true;
            for (int i = head[u]; ~i; i = edges[i].nxt) {
                Edge& e = edges[i];
                if (d[e.v] > d[u] + e.w) {
                    d[e.v] = d[u] + e.w;
                    Q.push((HeapNode){d[e.v], e.v});
                }
            }
        }
    }
};

}  // namespace ShortestPath