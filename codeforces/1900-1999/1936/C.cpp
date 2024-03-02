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
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

template <typename T>
struct Edge {
    int from, to;
    T cost;

    Edge() = default;
    Edge(int from, int to, T cost = 1) : from(from), to(to), cost(cost) {}

    // Edge e = Edge(); int to = e;
    operator int() const { return to; }
};

// [0, n)
template <typename Edge>
struct Graph {
    vector<vector<Edge>> g;

    Graph() = default;
    explicit Graph(int n) : g(n) {}

    size_t size() const {
        return g.size();
    }

    void add_directed_edge(const Edge &e) {
        g[e.from].push_back(e);
    }

    void add_undirected_edge(const Edge &e) {
        g[e.from].push_back(e);
        Edge rev = e;
        swap(rev.from, rev.to);
        g[rev.from].push_back(rev);
    }

    inline const vector<Edge> &operator[](const int &u) const {
        return g[u];
    }
};

template <typename Graph, typename T>
struct Dijkstra {
    Graph &g;
    T inf;

    vector<T> dist;
    vector<int> prev;
    vector<long long> num;

    Dijkstra(Graph &graph) : g(graph) {
        inf = numeric_limits<T>::max();
    }

    void init(int n) {
        dist.resize(n, inf);
        prev.resize(n, -1);
        num.resize(n, 0);

        for (int i = 0; i < n; i++) {
            dist[i] = inf;
            prev[i] = -1;
            num[i] = 0;
        }
    }

    // [0, n)
    void normal_dijkstra(int s) {
        // O(n ^ 2)
        int n = g.size();
        vector<bool> vis(n, 0);
        init(n);

        dist[s] = 0;
        num[s] = 1;

        for (int i = 0; i < n; i++) {
            int x;
            T m = inf;
            for (int y = 1; y <= n; y++) {
                if (!vis[y] && dist[y] <= m) {
                    m = dist[x = y];
                }
            }
            vis[x] = 1;
            for (auto e : g[x]) {
                int y = e.to;
                if (dist[y] > dist[x] + e.cost) {
                    dist[y] = dist[x] + e.cost;
                    prev[y] = x;
                    num[y] = num[x];
                } else if (dist[y] == dist[x] + e.cost) {
                    num[y] += num[x];
                }
            }
        }
    }

    void dijkstra(int s) {
        // O(m * log n)
        const T inf = numeric_limits<T>::max();
        int n = g.size();
        vector<bool> vis(n, 0);
        init(n);

        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> Q;

        dist[s] = 0;
        num[s] = 1;
        Q.push({0, s});
        while (!Q.empty()) {
            auto [dis, x] = Q.top();
            Q.pop();
            if (vis[x]) continue;
            vis[x] = 1;

            for (auto e : g[x]) {
                int y = e.to;
                if (dist[y] > dist[x] + e.cost) {
                    dist[y] = dist[x] + e.cost;
                    prev[y] = x;
                    num[y] = num[x];
                    Q.push({dist[y], y});
                } else if (dist[y] == dist[x] + e.cost) {
                    num[y] += num[x];
                }
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<long long> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    typedef Edge<long long> Ell;

    Graph<Ell> graph(n * (m + 1));

    auto get_id = [&](int x, int y) {
        return x * (m + 1) + y;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            graph.add_directed_edge(Ell(get_id(i, j), get_id(i, m), c[i]));
            graph.add_directed_edge(Ell(get_id(i, m), get_id(i, j), 0));
        }
    }

    for (int i = 0; i < m; i++) {
        vector<int> f(n);
        iota(f.begin(), f.end(), 0);
        sort(f.begin(), f.end(), [&](int x, int y) {
            return a[x][i] < a[y][i];
        });

        for (int j = 0; j < n; j++) {
            int idx1 = f[j];
            if (j != n - 1) {
                int idx2 = f[j + 1];
                graph.add_directed_edge(Ell(get_id(idx1, i), get_id(idx2, i), 0));
            }
            if (j != 0) {
                int idx2 = f[j - 1];
                graph.add_directed_edge(Ell(get_id(idx1, i), get_id(idx2, i), a[idx1][i] - a[idx2][i]));
            }
        }
    }
    Dijkstra<Graph<Ell>, long long> dij(graph);
    dij.dijkstra(get_id(0, m));
    cout << dij.dist[get_id(n - 1, m)] << endl;
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