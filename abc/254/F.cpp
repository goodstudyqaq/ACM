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

struct Info {
    int x;
    Info(int _x = 0) {
        x = _x;
    }
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    c.x = __gcd(a.x, b.x);
    return c;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<Info> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x;
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i].x;
    }

    vector<Info> c(n), d(n);
    for (int i = 0; i < n - 1; i++) {
        c[i].x = abs(a[i + 1].x - a[i].x);
        d[i].x = abs(b[i + 1].x - b[i].x);
    }

    SegmentTree<Info> seg1(c);
    SegmentTree<Info> seg2(d);

    while (q--) {
        int h1, h2, w1, w2;
        cin >> h1 >> h2 >> w1 >> w2;
        h1--, h2--;
        w1--, w2--;
        int g = a[h1].x + b[w1].x;
        if (w2 != w1) {
            g = __gcd(g, seg2.rangeQuery(w1, w2 - 1).x);
        }
        if (h1 != h2) {
            g = __gcd(g, seg1.rangeQuery(h1, h2 - 1).x);
        }
        cout << g << endl;
    }
    return 0;
}