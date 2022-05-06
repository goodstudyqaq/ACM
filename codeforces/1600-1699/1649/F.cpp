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

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template <class Info, class Merge = std::plus<Info>>
struct SegmentTree {
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << __lg(n)) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
            if (l == r) {
                info[rt] = init[l];
                return;
            }
            int m = l + r >> 1;
            build(lson);
            build(rson);
            push_up(rt);
        };
        build(0, n - 1, 1);
    }

    Info rangeQuery(int l, int r) {
        return rangeQuery(l, r, 0, n - 1, 1);
    }

    void update(int L, Info v) {
        return update(L, v, 0, n - 1, 1);
    }

   private:
    const int n;
    const Merge merge;
    vector<Info> info;
    void push_up(int rt) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1]);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson));
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void update(int L, Info& v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = merge(info[rt], v);
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
        }
        push_up(rt);
    }
};

const ll inf = numeric_limits<ll>::max() / 2;
struct MX {
    ll x;
    MX(ll _x = -inf) {
        x = _x;
    }
};

MX operator+(const MX& a, const MX& b) {
    MX res;
    res.x = max(a.x, b.x);
    return res;
}

struct Pair {
    ll a, b;
    ll sum;
    Pair(ll _a, ll _b) : a(_a), b(_b) {
        sum = _a + _b;
    }
    Pair() {
        a = -inf, b = -inf, sum = -inf - inf;
    }
};

Pair operator+(const Pair& a, const Pair& b) {
    Pair res;
    if (res.sum < a.sum) {
        res.sum = a.sum;
    }
    if (res.sum < b.sum) {
        res.sum = b.sum;
    }
    if (res.sum < a.a + b.b) {
        res.sum = a.a + b.b;
    }
    res.a = max(a.a, b.a);
    res.b = max(a.b, b.b);
    return res;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;

    vector a = vector(3, vector(n, 0LL));
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < n; i++) {
            cin >> a[j][i];
        }
    }
    vector sum1 = vector(n, 0LL);
    vector sum2 = vector(n, 0LL);

    for (int i = 0; i < n; i++) {
        sum1[i] += a[0][i];
        if (i) {
            sum1[i] += sum1[i - 1];
            sum1[i] -= a[1][i - 1];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        sum2[i] += a[2][i];
        if (i != n - 1) {
            sum2[i] += sum2[i + 1];
            sum2[i] -= a[1][i + 1];
        }
    }

    SegmentTree<MX> segment1(n);

    for (int i = 0; i < n; i++) {
        segment1.update(i, MX(sum1[i]));
    }

    typedef array<ll, 3> a3;
    vector<a3> help(q);
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        l--, r--;
        help[i] = {l, r, k};
    }
    sort(help.begin(), help.end());

    for (int i = 0; i < q; i++) {
        ll l = help[i][0], r = help[i][1], k = help[i][2];
        MX it = segment1.rangeQuery(l, r);
        if (r + 1 < n) {
            sum1[r + 1] = max(sum1[r + 1], it.x - k);
            segment1.update(r + 1, MX(sum1[r + 1]));
        }
    }
    debug(sum1);

    SegmentTree<Pair> segment2(n);

    for (int i = 0; i < n; i++) {
        segment2.update(i, Pair(sum1[i], sum2[i]));
    }

    ll ans = -inf;
    for (int i = 0; i < q; i++) {
        ll l = help[i][0], r = help[i][1], k = help[i][2];

        ll tmp = segment2.rangeQuery(l, r).sum;
        debug(l, r, tmp);

        ans = max(ans, tmp - k);
    }
    debug(sum2);

    ll sum3 = accumulate(a[1].begin(), a[1].end(), 0LL);
    debug(sum3, ans);
    cout << ans + sum3 << endl;
    return 0;
}