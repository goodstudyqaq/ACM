#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

struct VectorDijkstra {
    // 复杂度 O(mlogn) m <= n ^ 2, 适合稀疏图, 如果 m 很多则比普通的 dijkstra 更慢
    // 链式前向星
    struct Edge {
        int u, v, nxt;
        // 其他信息 如权重等。。
        ll w;
        int idx;
        // extra_info
    };
    vector<Edge> edges;
    vector<int> head;
    int ecnt;

    void add_edge(int u, int v, ll w, int idx) {
        edges[ecnt] = (Edge){u, v, head[u], w, idx};
        head[u] = ecnt++;
    }
    VectorDijkstra(int n, int m) {
        edges.resize(2 * m);
        head.resize(n + 1, -1);
        ecnt = 0;
    }

    struct HeapNode {
        ll d, u, idx;
        bool operator<(const HeapNode& rhs) const {
            return d > rhs.d;
        }
    };
    vector<bool> done;
    vector<ll> d;
    const ll inf = numeric_limits<ll>::max() / 2;
    vector<int> route;
    void dijkstra(int s, int n) {
        priority_queue<HeapNode> Q;
        d.clear(), d.resize(n + 1, inf);
        d[s] = 0;
        done.clear(), done.resize(n + 1, 0);
        Q.push((HeapNode){0, s, -1});
        while (!Q.empty()) {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if (done[u]) continue;
            done[u] = true;
            route.push_back(x.idx);
            for (int i = head[u]; ~i; i = edges[i].nxt) {
                Edge& e = edges[i];
                if (d[e.v] > d[u] + e.w) {
                    d[e.v] = d[u] + e.w;
                    Q.push((HeapNode){d[e.v], e.v, e.idx});
                }
            }
        }
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    VectorDijkstra dij(n, m);
    for (int i = 0; i < m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        dij.add_edge(u, v, d, i);
        dij.add_edge(v, u, d, i);
    }

    dij.dijkstra(1, n);

    for (auto v : dij.route) {
        if (v == -1) continue;
        cout << v + 1 << ' ';
    }
    cout << endl;
}