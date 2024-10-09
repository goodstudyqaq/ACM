#line 1 "704.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/structure/others/sparse-table.hpp"
using namespace std;

/*
半群：若集合 S 和二元运算 op : S X S -> S 满足对任意 x, y, z \in S 都有 op(op(x, y), z) = op(x, (y, z)), 称 (S, op) 为半群
幂等半群的区间查询,
1. fold 查询 [l, r) 的值

需要补充一些二分函数，O(log) 找到值
*/
// using F = function<int(int, int)>
template <typename T, typename F>
struct SparseTable {
    F f;
    vector<vector<T> > st;
    vector<int> lookup;

    SparseTable() = default;

    explicit SparseTable(const vector<T> &v, const F &f) : f(f) {
        const int n = (int)v.size();
        const int b = 32 - __builtin_clz(n);
        st.assign(b, vector<T>(n));
        for (int i = 0; i < v.size(); i++) {
            st[0][i] = v[i];
        }
        for (int i = 1; i < b; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
        lookup.resize(v.size() + 1);
        for (int i = 2; i < lookup.size(); i++) {
            lookup[i] = lookup[i >> 1] + 1;
        }
    }

    inline T fold(int l, int r) const {
        int b = lookup[r - l];
        return f(st[b][l], st[b][r - (1 << b)]);
    }
};

template <typename T, typename F>
SparseTable<T, F> get_sparse_table(const vector<T> &v, const F &f) {
    return SparseTable<T, F>(v, f);
}
#line 3 "/Users/guoshen/code/library2/graph/graph-template.hpp"
using namespace std;

template <typename T = int>
struct Edge {
    int from, to;
    T cost;
    int idx;

    Edge() = default;

    Edge(int from, int to, T cost = 1, int idx = -1)
        : from(from), to(to), cost(cost), idx(idx) {}

    operator int() const { return to; }
};

template <typename T = int>
struct Graph {
    vector<vector<Edge<T> > > g;
    int es;

    Graph() = default;

    explicit Graph(int n) : g(n), es(0) {}

    size_t size() const { return g.size(); }

    virtual void add_directed_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es++);
    }

    // virtual 可以被重载，实现多态
    virtual void add_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es);
        g[to].emplace_back(to, from, cost, es++);
    }

    void read(int M, int padding = -1, bool weighted = false,
              bool directed = false) {
        for (int i = 0; i < M; i++) {
            int a, b;
            cin >> a >> b;
            a += padding;
            b += padding;
            T c = T(1);
            if (weighted) cin >> c;
            if (directed)
                add_directed_edge(a, b, c);
            else
                add_edge(a, b, c);
        }
    }

    inline vector<Edge<T> > &operator[](const int &k) { return g[k]; }

    inline const vector<Edge<T> > &operator[](const int &k) const { return g[k]; }
};

template <typename T = int>
using Edges = vector<Edge<T> >;
#line 3 "/Users/guoshen/code/library2/graph/tree/rmq-lowest-common-ancestor.hpp"
/*
有点奇怪的写法，记录 dfs 时经过的每个点到 ord 里，维护每个点第一次在 ord 里的下标 in，求两个点的 lca 等价于ord 里 [in[a], in[b]] 中 dep 最小的那个点。感觉很合理。 
这个顺序就是欧拉序，即 dfs 时经过的点的顺序，但是叶子节点只算 1 次，而不算进出 2 次。
还有一个顺序叫括号序，即 dfs 时每个点进栈出栈的顺序，叶子节点会算 2 次。
*/

template <typename T = int>
struct RMQLowestCommonAncestor : Graph<T> {
   public:
    using Graph<T>::Graph;
    using Graph<T>::g;
    using F = function<int(int, int)>;

    void build(int root = 0) {
        ord.reserve(g.size() * 2 - 1);
        dep.reserve(g.size() * 2 - 1);
        in.resize(g.size());
        dfs(root, -1, 0);
        vector<int> vs(g.size() * 2 - 1);
        iota(begin(vs), end(vs), 0);
        F f = [&](int a, int b) { return dep[a] < dep[b] ? a : b; };
        st = get_sparse_table(vs, f);
    }

    int lca(int x, int y) const {
        if (in[x] > in[y]) swap(x, y);
        return x == y ? x : ord[st.fold(in[x], in[y])];
    }

   private:
    vector<int> ord, dep, in;
    SparseTable<int, F> st;

    void dfs(int idx, int par, int d) {
        in[idx] = (int)ord.size();
        ord.emplace_back(idx);
        dep.emplace_back(d);
        for (auto &to : g[idx]) {
            if (to != par) {
                dfs(to, idx, d + 1);
                ord.emplace_back(idx);
                dep.emplace_back(d);
            }
        }
    }
};
#line 4 "704.cpp"

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
unsigned int A, B, C;
inline unsigned int rng61() {
    A ^= A << 16;
    A ^= A >> 5;
    A ^= A << 1;
    unsigned int t = A;
    A = B;
    B = C;
    C ^= t ^ A;
    return C;
}
typedef unsigned int ui;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m >> A >> B >> C;
    // 输入树边
    RMQLowestCommonAncestor<> g(n);
    g.read(n - 1, -1, false, false);
    g.build(0);
    long long ans = 0;
    for (int i = 1; i <= m; i++) {
        unsigned int u = rng61() % n + 1, v = rng61() % n + 1;
        u--, v--;
        ans ^= (1LL * i * (g.lca(u, v) + 1));
    }
    cout << ans << endl;
}
