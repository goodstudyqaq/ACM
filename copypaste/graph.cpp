#include <bits/stdc++.h>
using namespace std;

namespace GraphReader {
/*
	1. 建图 建图的方式有很多，下面是几类
	*/
// vector 存图
void readGraphToVector(int n, int m) {
    // n: 点的范围 [1, n]
    // m: 边的个数
    vector<vector<int>> V;
    V.resize(n + 1);
    int u, v;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        V[u].push_back(v);
        // V[v].push_back(u); // 是否是双向边
    }
}

// 链式前向星
// https://oi-wiki.org//graph/save/#_14
struct GraphListReader {
    struct Edge {
        int u, v, nxt;
        // 其他信息 如权重等。。
        // extra_info
    };
    vector<Edge> edges;
    vector<int> head;
    int ecnt;

    void add_edge(int u, int v) {
        edges[ecnt] = (Edge){u, v, head[u]};
        head[u] = ecnt++;
    }

    void read(int n, int m) {
        head.clear(), head.resize(n + 1, -1);
        edges.resize(m);
        ecnt = 0;
        int u, v;
        for (int i = 1; i <= m; i++) {
            cin >> u >> v;
            add_edge(u, v);
        }
    }
};
}  // namespace GraphReader

namespace ShortestPath {
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