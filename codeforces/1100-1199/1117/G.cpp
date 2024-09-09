

#include <bits/stdc++.h>

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

template <typename T>
struct BIT {
#define lowbit(x) x & -x
    int n;
    vector<T> a;
    // [1, n]
    BIT(int n) : n(n), a(n + 1) {}
    BIT() {}

    void init(int _n) {
        n = _n;
        a = vector<T>(n + 1);
    }
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    // [1, x]
    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;
    vector<int> p(n + 1), ql(q), qr(q);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> ql[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> qr[i];
    }

    vector<int> lb(n + 1, 0), rb(n + 1, n + 1);

    vector<int> stk;
    for (int i = 1; i <= n; i++) {
        while (stk.size() && p[stk.back()] < p[i]) {
            rb[stk.back()] = i;
            stk.pop_back();
        }
        if (stk.size()) {
            lb[i] = stk.back();
        }
        stk.push_back(i);
    }

    debug(lb, rb);  // ok;

    vector<vector<int>> ql_idx(n + 1), qr_idx(n + 1);
    for (int i = 0; i < q; i++) {
        int l = ql[i];
        ql_idx[l].push_back(i);
        int r = qr[i];
        qr_idx[r].push_back(i);
    }

    vector<vector<int>> lb_idx(n + 1), rb_idx(n + 1);
    for (int i = 1; i <= n; i++) {
        lb_idx[lb[i] + 1].push_back(i);
        rb_idx[rb[i] - 1].push_back(i);
    }

    BIT<long long> bits(n), bits2(n);

    for (int i = 1; i <= n; i++) {
        bits.add(i, lb[i] + 1);
    }

    vector<long long> ans(q, 0);

    for (int i = 1; i <= n; i++) {
        for (auto &q_idx : ql_idx[i]) {
            int r = qr[q_idx];
            ans[q_idx] -= (bits.query(r) - bits.query(i - 1));
            ans[q_idx] -= (bits2.query(r) - bits2.query(i - 1)) * i;
        }

        for (auto &idx : lb_idx[i]) {
            bits2.add(idx, 1);
            bits.add(idx, -lb[idx] - 1);
        }
    }
    debug(ans);

    bits.init(n);
    bits2.init(n);

    for (int i = 1; i <= n; i++) {
        bits.add(i, rb[i] - 1);
    }

    for (int i = n; i >= 1; i--) {
        for (auto &q_idx : qr_idx[i]) {
            int l = ql[q_idx];
            ans[q_idx] += (bits.query(i) - bits.query(l - 1));
            ans[q_idx] += (bits2.query(i) - bits2.query(l - 1)) * i;
        }

        for (auto &idx : rb_idx[i]) {
            bits2.add(idx, 1);
            bits.add(idx, -rb[idx] + 1);
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] + qr[i] -ql[i] + 1 << ' ';
    }
    cout << endl;
}