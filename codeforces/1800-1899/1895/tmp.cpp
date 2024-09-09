#line 1 "G.cpp"
#include <bits/stdc++.h>

#line 3 "/Users/guoshen/code/library2/utils/utils.hpp"
using namespace std;

template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#line 2 "/Users/guoshen/code/library2/structure/bbst/treap.hpp"

template <typename T>
struct Node {
    int ch[2];
    T val, tag;
    int rk;
    int size = 0;  // 以当前节点为根子树的大小

    Node() {
        ch[0] = ch[1] = 0;
        val = 0;
    }
    Node(T val) : val(val) {
        tag = T();
        size = 1;
        rk = mrand();
        ch[0] = ch[1] = 0;
    }
};

template <typename T>
struct NonRotatingTreap {
    NonRotatingTreap() {
        nodes.clear();
        nodes.push_back(Node<T>());
        root = 0;
    }

    int root;
    vector<Node<T>> nodes;

    inline void push_up(int u) {
        nodes[u].size = nodes[nodes[u].ch[0]].size + 1 + nodes[nodes[u].ch[1]].size;
    }

    inline void push_tag(int x, T v) {
        if (x) {
            nodes[x].val += v;
            nodes[x].tag += v;
        }
    }

    void push_down(int u) {
        if (nodes[u].tag == T()) {
            return;
        }
        push_tag(nodes[u].ch[0], nodes[u].tag);
        push_tag(nodes[u].ch[1], nodes[u].tag);
        nodes[u].tag = T();
    }

    int new_node(T val) {
        int u = nodes.size();
        nodes.push_back(Node(val));
        return u;
    }

    void split_by_value(int u, T k, int &x, int &y) {
        if (!u) {
            x = y = 0;
            return;
        }
        push_down(u);
        if (nodes[u].val <= k) {
            x = u;
            split_by_value(nodes[u].ch[1], k, nodes[x].ch[1], y);
        } else {
            y = u;
            split_by_value(nodes[u].ch[0], k, x, nodes[y].ch[0]);
        }
        push_up(u);
    }

    void split_by_rank(int u, int rank, int &x, int &y) {
        if (!u) {
            x = 0, y = 0;
            return;
        }
        push_down(u);
        if (nodes[nodes[u].ch[0]].size + 1 <= rank) {
            x = u;
            split_by_rank(nodes[u].ch[1], rank - nodes[nodes[u].ch[0]].size - 1, nodes[x].ch[1], y);
        } else {
            y = u;
            split_by_rank(nodes[u].ch[0], rank, x, nodes[y].ch[0]);
        }
        push_up(u);
    }

    int merge(int x, int y) {
        if (!x || !y) {
            return x + y;
        }
        push_down(x);
        push_down(y);
        if (nodes[x].rk < nodes[y].rk) {
            nodes[x].ch[1] = merge(nodes[x].ch[1], y);
            push_up(x);
            return x;
        } else {
            nodes[y].ch[0] = merge(x, nodes[y].ch[0]);
            push_up(y);
            return y;
        }
    }

    inline void insert(T val) {
        int x, y;
        split_by_value(root, val, x, y);
        root = merge(merge(x, new_node(val)), y);
    }

    T qmin(int x) {
        while (nodes[x].ch[0]) {
            push_down(x);
            x = nodes[x].ch[0];
        }
        return nodes[x].val;
    }

    T qmax(int x) {
        while (nodes[x].ch[1]) {
            push_down(x);
            x = nodes[x].ch[1];
        }
        return nodes[x].val;
    }
};
#line 4 "G.cpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

void solve() {
    NonRotatingTreap<long long> treap;

    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<long long> r(n), b(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> r[i];
        ans += r[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        ans += b[i];
    }

    auto del_zero = [&]() {
        int x, y;
        treap.split_by_value(treap.root, 0, x, y);
        treap.root = y;
    };

    auto del_kmax = [&](long long k) {
        int sz = treap.nodes[treap.root].size;
        k = min(k, 1LL * sz);
        if (k == 0) {
            return 0LL;
        }
        int x, y;
        treap.split_by_rank(treap.root, sz - k, x, y);
        int left_mx = treap.qmax(x);
        int right_mi = treap.qmin(y);
        if (left_mx < right_mi) {
            treap.push_tag(y, -1);
            treap.root = treap.merge(x, y);
        } else {
            // 相等
            int left_x, right_x;
            int left_y, right_y;

            treap.split_by_value(x, left_mx - 1, left_x, right_x);
            treap.split_by_value(y, left_mx, left_y, right_y);

            treap.push_tag(left_y, -1);
            treap.push_tag(right_y, -1);
            treap.merge(treap.merge(left_x, left_y), treap.merge(right_x, right_y));
        }
        return k;
    };

    for (int i = 0; i < n; i++) {
        long long tmp = min(r[i], b[i]);
        ans -= tmp;
        if (s[i] == '0') {
            tmp = r[i] - tmp;
            long long k = del_kmax(tmp);
            ans -= k;
            del_zero();
        } else {
            tmp = r[i] - tmp;
            if (tmp) {
                treap.insert(tmp);
            }
        }
    }
    cout << ans << endl;
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
