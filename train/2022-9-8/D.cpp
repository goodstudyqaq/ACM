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
    int v;
    Info(int x = 0) {
        v = x;
    }
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    c.v = gcd(a.v, b.v);
    return c;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<Info> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].v;
    }
    SegmentTree<Info> seg(a);

    vector<vector<int>> V(n);

    for (int i = 0; i < n; i++) {
        int l = i, r = n - 1;
        int ans = -1;

        while (l <= r) {
            int mid = l + r >> 1;
            if (seg.rangeQuery(i, mid).v >= mid - i + 1) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if (seg.rangeQuery(i, ans).v == ans - i + 1) {
            V[ans].push_back(i);
        }
    }
    int res = 0, last = -1;
    for (int i = 0; i < n; i++) {
        for (auto it : V[i]) {
            if (it > last) {
                res++;
                last = i;
            }
        }
        cout << res << ' ';
    }
    return 0;
}