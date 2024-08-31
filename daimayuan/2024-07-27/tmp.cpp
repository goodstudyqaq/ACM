#line 1 "F.cpp"
#include <bits/stdc++.h>

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

    void add_directed_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es++);
    }

    void add_edge(int from, int to, T cost = 1) {
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
#line 2 "/Users/guoshen/code/library2/graph/tree/heavy-light-decomposition.hpp"
template <typename T = int>
struct HeavyLightDecomposition : Graph<T> {
   public:
    using Graph<T>::Graph;
    using Graph<T>::g;
    /*
        sz[u]: u 子树大小
        par[u]: u 的父亲
        dep[u]: u 的深度
        in[u]: dfs 序 u 进来的时间戳
        out[u]: dfs 序 u 出去的时间戳
        head[u]: u 所在的重链的起始位置
        rev[t]: 时间戳为 t 时对应的节点
    */
    vector<int> sz, in, out, head, rev, par, dep;

    void build(int root = 0) {
        sz.assign(g.size(), 0);
        in.assign(g.size(), 0);
        out.assign(g.size(), 0);
        head.assign(g.size(), 0);
        rev.assign(g.size(), 0);
        par.assign(g.size(), 0);
        dep.assign(g.size(), 0);

        dfs_sz(root, -1, 0);
        int t = 0;
        head[root] = root;
        dfs_hld(root, -1, t);
    }

    int lca(int u, int v) const {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) return u;
        }
    }

   private:
    void dfs_sz(int u, int pre, int d) {
        dep[u] = d;
        par[u] = pre;
        sz[u] = 1;
        if (g[u].size() && g[u][0] == pre) swap(g[u][0], g[u].back());
        for (auto &v : g[u]) {
            if (v == pre) continue;
            dfs_sz(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[g[u][0]] < sz[v]) swap(g[u][0], v);
        }
    }

    void dfs_hld(int u, int pre, int &times) {
        in[u] = times++;
        rev[in[u]] = u;
        for (auto &v : g[u]) {
            if (v == pre) continue;
            head[v] = (g[u][0] == v ? head[u] : v);
            dfs_hld(v, u, times);
        }
        out[u] = times;
    }
};
#line 2 "/Users/guoshen/code/library2/math/mint.hpp"
using namespace std;
template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a;
        swap(a, m);
        u -= t * v;
        swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <typename T>
class Modular {
   public:
    using Type = typename decay<decltype(T::value)>::type;

    constexpr Modular() : value() {}
    template <typename U>
    Modular(const U& x) {
        value = normalize(x);
    }

    template <typename U>
    static Type normalize(const U& x) {
        Type v;
        if (-mod() <= x && x < mod())
            v = static_cast<Type>(x);
        else
            v = static_cast<Type>(x % mod());
        if (v < 0) v += mod();
        return v;
    }

    const Type& operator()() const { return value; }
    template <typename U>
    explicit operator U() const { return static_cast<U>(value); }
    constexpr static Type mod() { return T::value; }

    Modular& operator+=(const Modular& other) {
        if ((value += other.value) >= mod()) value -= mod();
        return *this;
    }
    Modular& operator-=(const Modular& other) {
        if ((value -= other.value) < 0) value += mod();
        return *this;
    }
    template <typename U>
    Modular& operator+=(const U& other) { return *this += Modular(other); }
    template <typename U>
    Modular& operator-=(const U& other) { return *this -= Modular(other); }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    Modular operator++(int) {
        Modular result(*this);
        *this += 1;
        return result;
    }
    Modular operator--(int) {
        Modular result(*this);
        *this -= 1;
        return result;
    }
    Modular operator-() const { return Modular(-value); }

    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
        uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
        uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
        asm(
            "divl %4; \n\t"
            : "=a"(d), "=d"(m)
            : "d"(xh), "a"(xl), "r"(mod()));
        value = m;
#else
        value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
        return *this;
    }
    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type& operator*=(const Modular& rhs) {
        long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
        value = normalize(value * rhs.value - q * mod());
        return *this;
    }
    template <typename U = T>
    typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
        value = normalize(value * rhs.value);
        return *this;
    }

    Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

    friend const Type& abs(const Modular& x) { return x.value; }

    template <typename U>
    friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

    template <typename U>
    friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

    template <typename V, typename U>
    friend V& operator>>(V& stream, Modular<U>& number);

   private:
    Type value;
};

template <typename T>
bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U>
bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U>
bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T>
bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U>
bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U>
bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T>
bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T>
Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U>
Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U>
Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T>
Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U>
Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U>
Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T>
Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U>
Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U>
Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T>
Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U>
Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U>
Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template <typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
    assert(b >= 0);
    Modular<T> x = a, res = 1;
    U p = b;
    while (p > 0) {
        if (p & 1) res *= x;
        x *= x;
        p >>= 1;
    }
    return res;
}

template <typename T>
bool IsZero(const Modular<T>& number) {
    return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
    return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
    return stream << number();
}

// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
    typename common_type<typename Modular<T>::Type, long long>::type x;
    stream >> x;
    number.value = Modular<T>::normalize(x);
    return stream;
}

/*
using ModType = int;

struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/

/*
constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);

Mint C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    while ((int)fact.size() < n + 1) {
        fact.push_back(fact.back() * (int)fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}

Mint A(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    while ((int)fact.size() < n + 1) {
        fact.push_back(fact.back() * (int)fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[n - k];
}

*/
#line 2 "/Users/guoshen/code/library2/structure/segment-tree/segment-tree.hpp"
using namespace std;
/*
半群单点更新，区间查询操作
半群定义见 sparse-table.hpp
todo: find_first + find_last
 */
/*
struct Info {
    // 默认值
    Info() {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) { 
        return Info(); 
    }
    string to_string() {
        return "";
    }
};
*/

template <typename Info>
struct SegmentTree {
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
    SegmentTree(int n) : n(n), merge(Info::merge), info(4 << __lg(n)) {}
    SegmentTree(const vector<Info>& init) : SegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
            if (l == r) {
                info[rt] = init[l];
                return;
            }
            int m = l + r >> 1;
            build(lson);
            build(rson);
            push_up(rt, l, r);
        };
        build(0, n - 1, 1);
    }

    Info rangeQuery(int l, int r) {
        return rangeQuery(l, r - 1, 0, n - 1, 1);
    }

    // 单点更新, 会将下标为 L 的点与 v 进行 merge 操作
    void update(int L, const Info& v) {
        return update(L, v, 0, n - 1, 1);
    }

    // 单点赋值, 会将下标为 L 的点直接赋值为 v
    void assign(int L, const Info& v) {
        return assign(L, v, 0, n - 1, 1);
    }

    string to_string(int u, int l, int r, string prefix, bool is_lch) {
        if (l > r) {
            return "";
        }
        string m_prefix = prefix + (u != 1 ? ((is_lch ? "╭── " : "╰── ")) : "");
        string m_res = info[u].to_string() + "\n";
        string l_res, r_res;
        if (l < r) {
            string l_prefix = prefix + ((u != 1) ? (is_lch ? "    " : "│   ") : "");
            string r_prefix = prefix + ((u != 1) ? (!is_lch ? "    " : "│   ") : "");
            l_res = to_string(u * 2, l, l + r >> 1, l_prefix, true);
            r_res = to_string(u * 2 + 1, (l + r >> 1) + 1, r, r_prefix, false);
        }
        return l_res + m_prefix + m_res + r_res;
    }
    string to_string() {
        return to_string(1, 0, n - 1, "", false);
    }

   private:
    const int n;
    vector<Info> info;
    const function<Info(const Info&, const Info&, int, int)> merge;

    void push_up(int rt, int l, int r) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1], l, r);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson), l, r);
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void update(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = merge(info[rt], v, l, r);
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
        }
        push_up(rt, l, r);
    }

    void assign(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            assign(L, v, lson);
        } else {
            assign(L, v, rson);
        }
        push_up(rt, l, r);
    }
#undef lson
#undef rson
};

template <typename Info>
string to_string(SegmentTree<Info> st) {
    return "\n" + st.to_string();
}
#line 6 "F.cpp"

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

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

struct Info {
    // 默认值
    Mint a1, b1;
    Mint a2, b2;
    Info(Mint a1 = 1, Mint b1 = 0, Mint a2 = 1, Mint b2 = 0) : a1(a1), b1(b1), a2(a2), b2(b2) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        // a1, b1 -> left_info(right_info)
        Mint a1 = left_info.a1 * right_info.a1;
        Mint b1 = left_info.a1 * right_info.b1 + left_info.b1;

        // a2, b2 -> right_info(left_info)
        Mint a2 = right_info.a2 * left_info.a2;
        Mint b2 = right_info.a2 * left_info.b2 + right_info.b2;
        return Info(a1, b1, a2, b2);
    }
    string to_string() {
        return "";
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    SegmentTree<Info> st(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    HeavyLightDecomposition<> hld(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }

    hld.build();
    // debug(hld.rev);

    for (int i = 0; i < n; i++) {
        int u = hld.rev[i];
        st.assign(i, Info(a[u], b[u], a[u], b[u]));
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p, c, d;
            cin >> p >> c >> d;
            int timestamp = hld.in[p];
            st.assign(timestamp, Info(c, d, c, d));
        } else {
            int u, v, x;
            cin >> u >> v >> x;
            // u 在里面， v 在外面
            Info left(1, 0), right(1, 0);
            while (true) {
                if (hld.head[u] == hld.head[v]) {
                    int idx1 = hld.in[u];
                    int idx2 = hld.in[v];
                    auto it = st.rangeQuery(min(idx1, idx2), max(idx1, idx2) + 1);
                    if (idx1 < idx2) {
                        Info tmp = Info(it.a2, it.b2);
                        right = Info::merge(right, tmp, 0, 0);
                    } else {
                        Info tmp = Info(it.a1, it.b1);
                        left = Info::merge(tmp, left, 0, 0);
                    }
                    break;
                } else {
                    if (hld.in[u] > hld.in[v]) {
                        int h = hld.head[u];
                        int idx1 = hld.in[h];
                        int idx2 = hld.in[u];
                        auto it = st.rangeQuery(idx1, idx2 + 1);
                        Info tmp = Info(it.a1, it.b1);
                        left = Info::merge(tmp, left, 0, 0);
                        u = hld.par[h];
                    } else {
                        int h = hld.head[v];
                        int idx1 = hld.in[h];
                        int idx2 = hld.in[v];
                        auto it = st.rangeQuery(idx1, idx2 + 1);
                        Info tmp = Info(it.a2, it.b2);
                        right = Info::merge(right, tmp, 0, 0);
                        // debug(right.a1, right.b1, right.a2, right.b2);
                        v = hld.par[h];
                    }
                }
            }
            // debug(left.a1, left.b1);
            // debug(right.a1, right.b1);
            Info res = Info::merge(right, left, 0, 0);
            cout << res.a1 * x + res.b1 << endl;
        }
    }
    return 0;
}
