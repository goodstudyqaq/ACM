#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

template <typename T>
struct Fenwick {
#define lowbit(x) x & -x
    const int n;
    vector<T> a;
    Fenwick(int n) : n(n), a(n + 1) {}
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};

struct Query {
    int t;
    ll l, r, x;
    int i, j;
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m, q;
    cin >> n >> m >> q;

    Fenwick<ll> cows(m + 1);
    map<int, int> M;
    vector<Query> querys(q);
    map<int, vector<int>> V;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            querys[i].t = 1;
            querys[i].l = l, querys[i].r = r, querys[i].x = x;
            querys[i] = (Query){t, l, r, x};
        } else if (t == 2) {
            int j, x;
            cin >> j >> x;
            querys[i].t = 2;
            querys[i].i = j;
            querys[i].x = x;
            M[j] = i;
        } else {
            int a, b;
            cin >> a >> b;
            querys[i].t = 3;
            querys[i].i = a, querys[i].j = b;
            if (M.count(a)) {
                V[M[a]].push_back(i);
            }
        }
    }
    // debug("zz");
    debug(M);
    debug(V);

    map<int, ll> sub_ans;
    for (int times = 0; times < q; times++) {
        // debug(times, querys[times].t, querys[times].l, querys[times].r);
        if (querys[times].t == 1) {
            cows.add(querys[times].l, querys[times].x);
            cows.add(querys[times].r + 1, -querys[times].x);
        } else if (querys[times].t == 2) {
            ll i = querys[times].i, x = querys[times].x;
            if (V[times].size()) {
                for (auto idx : V[times]) {
                    int j = querys[idx].j;
                    ll it = cows.query(j);
                    sub_ans[idx] = x - it;
                }
            }
        } else {
            int i = querys[times].i, j = querys[times].j;
            // debug(j, cows.query(j));
            ll val = cows.query(j) + sub_ans[times];
            cout << val << endl;
        }
    }

    return 0;
}