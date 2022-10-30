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
/*
 @brief Graph template
 @docs docs/graph_template.md
 */

struct Edge {
    int from, to;
    int cost;

    Edge() = default;
    Edge(int from, int to, int cost = 1) : from(from), to(to), cost(cost) {}

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

// 一般形式的 dijkstra
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
                } else {
                    num[y] += num[x];
                }
            }
        }
    }
};

struct Subset {
    /*
    枚举 status 的全部子集
    */
    int status;
    Subset(int status) : status(status) {}
    struct Iterator {
        int i;
        int status;
        bool ok;
        Iterator(int _i, int _s, bool ok = true) : i(_i), status(_s), ok(ok) {}
        int operator*() const {
            return i;
        }
        bool operator!=(const Iterator &a) const {
            return (i != a.i || ok != a.ok);
        }
        Iterator &operator++() {
            i = (i - 1) & status;
            ok = (i != status);
            return *this;
        }
    };
    Iterator begin() const {
        return Iterator(status, status, true);
    }
    Iterator end() const {
        // 作为结束条件，处理完 0 之后，会有 -1 & status = status
        return Iterator(status, status, false);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Graph<Edge> g(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g.add_undirected_edge(Edge(u, v));
    }

    int f;
    cin >> f;
    vector<int> friends(f);
    for (int i = 0; i < f; i++) {
        cin >> friends[i];
        friends[i]--;
    }

    int k;
    cin >> k;
    vector<int> nocar(k);
    vector<int> nocar_idx(f);
    for (int i = 0; i < k; i++) {
        cin >> nocar[i];
        nocar[i]--;
        nocar_idx[nocar[i]] = 1;
    }

    Dijkstra<Graph<Edge>, int> dij(g);

    dij.dijkstra(0);
    vector<int> d1 = dij.dist;
    vector<vector<int>> nocar_dis(k);
    for (int i = 0; i < k; i++) {
        int u = friends[nocar[i]];
        dij.dijkstra(u);
        nocar_dis[i] = dij.dist;

        debug(u, nocar_dis[i]);
    }

    debug(d1);

    const int LIMIT = 1 << k;
    vector<bool> vis(k);
    vector<vector<bool>> status = vector(LIMIT, vector(k, false));

    function<void(int, int, int)> dfs = [&](int u, int idx, int st) {
        if (idx != -1) {
            status[st][idx] = 1;
        }
        for (int i = 0; i < k; i++) {
            if (vis[i]) continue;
            int v = friends[nocar[i]];
            int one_to_v = d1[v];
            int one_to_u = d1[u];
            int tmp;
            if (idx == -1) {
                tmp = d1[v];
            } else {
                tmp = nocar_dis[idx][v];
            }
            if (one_to_v == one_to_u + tmp) {
                vis[i] = 1;
                dfs(v, i, st + (1 << i));
                vis[i] = 0;
            }
        }
    };
    dfs(0, -1, 0);
    // for (int i = 0; i < LIMIT; i++) {
    //     for (int j = 0; j < k; j++) {
    //         if (status[i][j]) {
    //             debug(i, j);
    //         }
    //     }
    // }

    vector<vector<bool>> ok = vector(f, vector(LIMIT, false));

    for (int i = 0; i < f; i++) {
        if (nocar_idx[i]) continue;
        ok[i][0] = 1;
        int v = friends[i];
        for (int j = 0; j < LIMIT; j++) {
            int now = j;
            while (now) {
                int it = now & -now;
                int c = __builtin_ctz(it);
                if (status[j][c] && d1[v] == d1[friends[nocar[c]]] + nocar_dis[c][v]) {
                    ok[i][j] = 1;
                    break;
                }
                now -= it;
            }
            // if (ok[i][j]) {
            //     debug(i, j);
            // }
        }
    }

    vector<bool> dp(LIMIT);
    dp[0] = 1;
    for (int i = 0; i < f; i++) {
        if (nocar_idx[i]) continue;
        vector<bool> ndp(LIMIT);
        for (int j = 0; j < LIMIT; j++) {
            // 枚举 j 的补集的子集
            if (dp[j]) {
                debug(i, j);
                int buji = LIMIT - j - 1;
                auto sub = Subset(buji);
                for (Subset::Iterator it = sub.begin(); it != sub.end(); ++it) {
                    if (ok[i][*it]) {
                        int new_s = *it + j;
                        ndp[new_s] = 1;
                    }
                }
            }
        }
        dp = ndp;
    }
    debug(dp);

    int ans = 0;
    for (int i = 0; i < LIMIT; i++) {
        if (dp[i]) {
            ans = max(ans, __builtin_popcount(i));
        }
    }
    cout << k - ans << endl;
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
}