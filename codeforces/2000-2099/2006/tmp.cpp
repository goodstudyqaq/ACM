#line 1 "C.cpp"
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
#line 4 "C.cpp"

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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> no_same(n, n);
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] == a[i + 1]) {
            no_same[i] = no_same[i + 1];
        } else {
            no_same[i] = i + 1;
        }
    }
    vector<int> b(n);
    for (int i = 0; i < n - 1; i++) {
        b[i] = abs(a[i] - a[i + 1]);
    }

    auto f = [&](int a, int b) -> int {
        return gcd(a, b);
    };
    using F = function<int(int, int)>;

    auto st = SparseTable<int, F>(b, [&](int a, int b) {
        return gcd(a, b);
    });

    long long ans = 1;
    for (int i = 0; i < n - 1; i++) {
        int l = no_same[i], r = n - 1;
        ans += l - i;
        int res = -1;
        while (l <= r) {
            // debug(l, r);
            int m = l + r >> 1;
            // [i, m - 1]
            int val = st.fold(i, m);
            while (val % 2 == 0) val /= 2;
            if (val == 1) {
                res = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        // debug(i, no_same[i], res);
        if (res != -1) {
            ans += n - res;
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
