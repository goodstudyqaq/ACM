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
template <class Info, class Tag, class Merge = std::plus<Info>>
struct LazySegmentTree {
    LazySegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(vector<Info> &init) : LazySegmentTree(init.size()) {
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

    void update(int L, const Info &v) {
        update(L, v, 0, n - 1, 1);
    }

    void rangeUpdate(int L, int R, const Tag &v) {
        return rangeUpdate(L, R, v, 0, n - 1, 1);
    }

    Info rangeQuery(int L, int R) {
        return rangeQuery(L, R, 0, n - 1, 1);
    }

    int find_first(int ll, int rr, const function<bool(const Info &)> &f) {
        return find_first(ll, rr, f, 0, n - 1, 1);
    }

    int find_last(int ll, int rr, const function<bool(const Info &)> &f) {
        return find_last(ll, rr, f, 0, n - 1, 1);
    }

    const int n;
    const Merge merge;
    vector<Info> info;
    vector<Tag> tag;
    void push_up(int rt) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1]);
    }

    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push_down(int rt) {
        apply(rt << 1, tag[rt]);
        apply(rt << 1 | 1, tag[rt]);
        tag[rt] = Tag();
    }

    void update(int L, const Info &v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        push_down(rt);
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
        }
        push_up(rt);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        push_down(rt);
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson));
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void rangeUpdate(int L, int R, const Tag &v, int l, int r, int rt) {
        if (L <= l && r <= R) {
            apply(rt, v);
            return;
        }
        int m = l + r >> 1;
        push_down(rt);
        if (L <= m) {
            rangeUpdate(L, R, v, lson);
        }
        if (R > m) {
            rangeUpdate(L, R, v, rson);
        }
        push_up(rt);
    }

    int find_first_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(rt);
        int res;
        if (f(info[rt << 1])) {
            res = find_first_knowingly(f, lson);
        } else {
            res = find_first_knowingly(f, rson);
        }
        push_up(rt);
        return res;
    }

    int find_first(int L, int R, const function<bool(const Info &)> f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_first_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        push_down(rt);
        int res = -1;
        if (L <= m) {
            res = find_first(L, R, f, lson);
        }
        if (R > m && res == -1) {
            res = find_first(L, R, f, rson);
        }
        push_up(rt);
        return res;
    }

    int find_last_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(rt);
        int res;
        if (f(info[rt << 1 | 1])) {
            res = find_last_knowingly(f, rson);
        } else {
            res = find_last_knowingly(f, lson);
        }
        push_up(rt);
        return res;
    }

    int find_last(int L, int R, const function<bool(const Info &)> f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_last_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        push_down(rt);
        int res = -1;
        if (R > m) {
            res = find_last(L, R, f, rson);
        }
        if (L <= m && res == -1) {
            res = find_last(L, R, f, lson);
        }
        push_up(rt);
        return res;
    }
};

struct Tag {
    int x;
    Tag(int _x) : x(_x) {}
    Tag() { x = -1; }
    void apply(const Tag &v) {
        if (v.x == -1) return;
        x = v.x;
    }
};

struct Info {
    int sum;
    int l, r;
    Info(int _x, int idx) {
        sum = _x;
        l = r = idx;
    }

    Info() {
        sum = 0;
        l = r = -1;
    }

    void apply(const Tag &v) {
        if (v.x == -1) return;
        sum = (r - l + 1) * v.x;
    }

    friend Info operator+(const Info &a, const Info &b) {
        Info res;
        res.l = a.l, res.r = b.r;
        res.sum = a.sum + b.sum;
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    const int maxn = 5e5 + 1;

    vector<Info> res(maxn);
    for (int i = 0; i < maxn; i++) {
        res[i] = Info(0, i);
    }

    LazySegmentTree<Info, Tag> seg(res);
    int n, q;
    cin >> n >> q;

    auto add = [&](int idx) {
        Info val = seg.rangeQuery(idx, idx);
        if (val.sum == 0) {
            val.sum = 1;
            seg.update(idx, val);
        } else {
            int idx2 = seg.find_first(idx, maxn - 1, [&](const Info &info) -> bool {
                return info.sum != info.r - info.l + 1;
            });
            seg.rangeUpdate(idx, idx2 - 1, Tag(0));
            Info val2 = Info(1, idx2);
            seg.update(idx2, val2);
        }
    };

    auto del = [&](int idx) {
        Info val = seg.rangeQuery(idx, idx);
        if (val.sum == 1) {
            val.sum = 0;
            seg.update(idx, val);
        } else {
            int idx2 = seg.find_first(idx, maxn - 1, [&](const Info &info) -> bool {
                return info.sum != 0;
            });

            seg.rangeUpdate(idx, idx2 - 1, Tag(1));
            Info val2 = Info(0, idx2);
            seg.update(idx2, val2);
        }
    };

    auto out = [&]() {
        Info sum = seg.rangeQuery(0, maxn - 1);

        int l = 0, r = maxn - 1;
        int ans = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            Info tmp = seg.rangeQuery(0, mid);
            if (tmp.sum == sum.sum) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    };

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int val = a[i];
        // +1
        add(val);
    }

    // for (int i = 1; i <= 10; i++) {
    //     debug(i, seg.rangeQuery(i, i).sum);
    // }

    while (q--) {
        int k, l;
        cin >> k >> l;
        del(a[k - 1]);
        a[k - 1] = l;
        add(a[k - 1]);
        out();
    }
    return 0;
}