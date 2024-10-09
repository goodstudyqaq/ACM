#line 1 "D.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/structure/others/sparse-table.hpp"
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

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


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
#line 4 "D.cpp"

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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    using F = function<int(int, int)>;
    F f = [&](int a, int b) {
        return gcd(a, b);
    };

    auto st1 = SparseTable<int, F>(a, f);
    auto st2 = SparseTable<int, F>(b, f);

    int mx = -1;
    long long ans = 0;

    auto get_mid_change = [&](int idx, int r, SparseTable<int, F> &st, int f) -> int {
        int val = st.fold(idx, r + 1);

        int l2 = r, r2 = n - 1;
        int ans = -1;
        while (l2 <= r2) {
            int m = l2 + r2 >> 1;
            if (st.fold(idx, m + 1) == val) {
                ans = m;
                l2 = m + 1;
            } else {
                r2 = m - 1;
            }
        }
        return ans;
    };

    // map<pair<int, int>, int> cache2;
    auto cache2 = vect(-1, n, 3);
    auto get_right_change = [&](int idx, SparseTable<int, F> &st, int flag) -> int {
        if (cache2[idx][flag] != -1) {
            return cache2[idx][flag];
        }

        int val = st.fold(idx, n);
        debug(idx, val);
        int l2 = idx, r2 = n - 1;
        int ans = -1;
        while (l2 <= r2) {
            int m = l2 + r2 >> 1;
            if (st.fold(m, n) == val) {
                ans = m;
                l2 = m + 1;
            } else {
                r2 = m - 1;
            }
        }
        return cache2[idx][flag] = ans;
    };

    for (int l = 0; l < n; l++) {
        int lefta = (l == 0 ? 0 : st1.fold(0, l));
        int leftb = (l == 0 ? 0 : st2.fold(0, l));

        int now1 = get_mid_change(l, l, st2, 2);
        int now2 = get_mid_change(l, l, st1, 1);
        int now3 = l + 1 < n ? get_right_change(l + 1, st1, 1) - 1 : l;
        int now4 = l + 1 < n ? get_right_change(l + 1, st2, 2) - 1 : l;
        int now = l;

        debug(l);
        while (now < n) {
            int go = min({now1, now2, now3, now4});

            // debug(now);
            int mida = st2.fold(l, now + 1);
            int midb = st1.fold(l, now + 1);

            int righta = go + 1 < n ? st1.fold(go + 1, n) : 0;
            int rightb = go + 1 < n ? st2.fold(go + 1, n) : 0;
            int tmp = gcd(gcd(lefta, mida), righta);
            int tmp2 = gcd(gcd(leftb, midb), rightb);
            long long number = go - now + 1;
            if (mx < tmp + tmp2) {
                mx = tmp + tmp2;
                ans = number;
            } else if (mx == tmp + tmp2) {
                ans += number;
            }
            now = go + 1;
            if (now == n) break;

            if (now1 < now) {
                now1 = get_mid_change(l, now, st2, 2);
            }
            if (now2 < now) {
                now2 = get_mid_change(l, now, st1, 1);
            }
            if (now3 < now) {
                now3 = now + 1 < n ? get_right_change(now + 1, st1, 1) - 1 : now;
            }
            if (now4 < now) {
                now4 = now + 1 < n ? get_right_change(now + 1, st2, 2) - 1 : now;
            }
        }
    }
    cout << mx << ' ' << ans << endl;
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
