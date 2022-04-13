#include <bits/stdc++.h>
using namespace std;
namespace Network {
template <typename IntType>
class IntValue {
   public:
    using ValueType = IntType;

    static bool greater_than_zero(ValueType x) { return x > 0; }
};

template <int PRECISION>
class DoubleValue {
   public:
    using ValueType = double;
    constexpr static double EPSILON = pow(10, -PRECISION);

    static bool greater_than_zero(ValueType x) { return x > EPSILON; }
};

//下标从0到N-1
//最小费用最大流，求最大费用只需取相反数，结果取相反数即可。
template <typename Derived = Network::IntValue<int>>
struct SPFA {
    using T = typename Derived::ValueType;

   public:
    SPFA(int n, int m = 0) : N(n), head(n, -1), pre(n), dis(n), vis(n) {
        edges.reserve(m);
    }
    SPFA() {}

    void addedge(int u, int v, T cap, T cost) {
        edges.push_back(Edge(v, head[u], cap, 0, cost));
        head[u] = int(edges.size() - 1);
        edges.push_back(Edge(u, head[v], 0, 0, -cost));
        head[v] = int(edges.size() - 1);
    }

    T minCostMaxflow(int s, int t, T& cost) {
        T flow = 0;
        cost = 0;
        while (spfa(s, t)) {
            T Min = inf;
            for (int i = pre[t]; ~i; i = pre[edges[i ^ 1].to]) {
                if (greater_than_zero(Min - (edges[i].cap - edges[i].flow))) {
                    Min = edges[i].cap - edges[i].flow;
                }
            }
            for (int i = pre[t]; ~i; i = pre[edges[i ^ 1].to]) {
                edges[i].flow += Min;
                edges[i ^ 1].flow -= Min;
                cost += edges[i].cost * Min;
            }
            flow += Min;
        }
        return flow;
    }

   private:
    const T inf = numeric_limits<T>::max() / 2;
    struct Edge {
        int to, next;
        T cap, flow, cost;
        Edge(int _to, int _next, T _cap, T _flow, T _cost) : to(_to), next(_next), cap(_cap), flow(_flow), cost(_cost) {}
        Edge() {}
    };
    int N;
    vector<int> head;
    vector<Edge> edges;
    vector<T> pre, dis;
    vector<bool> vis;

    bool spfa(int s, int t) {
        queue<int> q;
        for (int i = 0; i < N; i++) {
            dis[i] = inf;
            vis[i] = false;
            pre[i] = -1;
        }
        dis[s] = 0;
        vis[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (int i = head[u]; ~i; i = edges[i].next) {
                int v = edges[i].to;
                if (greater_than_zero(edges[i].cap - edges[i].flow) && greater_than_zero(dis[v] - (dis[u] + edges[i].cost))) {
                    dis[v] = dis[u] + edges[i].cost;
                    pre[v] = i;
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        if (pre[t] == -1) return 0;
        return 1;
    }

    static bool greater_than_zero(T x) {
        return Derived::greater_than_zero(x);
    }
};
}  // namespace Network