#line 1 "E1.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/structure/others/sparse-table.hpp"
using namespace std;

/*
半群：若集合 S 和二元运算 op : S X S -> S 满足对任意 x, y, z \in S 都有 op(op(x, y), z) = op(x, (y, z)), 称 (S, op) 为半群
幂等半群的区间查询,
1. fold 查询 [l, r) 的值

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
#line 4 "E1.cpp"

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
    int n;
    cin >> n;
    vector<int> w(n);
    vector<vector<int>> V(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<int> l(n), r(n);
    int t = 0;
    function<void(int, int)> dfs = [&](int u, int pre) {
        l[u] = t++;
        for (int v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
        }
        r[u] = t;
    };
    dfs(0, -1);
    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        int loc = l[i];
        val[loc] = w[i];
    }

    auto st = get_sparse_table(val, [&](int a, int b) {
        return max(a, b);
    });

    int find = -1;
    for (int i = 0; i < n; i++) {
        int _l = l[i], _r = r[i];
        int mx1 = w[i];

        int mx2 = 0;
        if (_l != 0) {
            mx2 = max(mx2, st.fold(0, _l));
        }
        if (_r != n) {
            mx2 = max(mx2, st.fold(_r, n));
        }
        if (mx2 > mx1) {
            if (find == -1 || w[find] < mx1) {
                find = i;
            }
        }
    }
    cout << find + 1 << '\n';
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
