#include <bits/stdc++.h>
using namespace std;

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

   private:
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
};

const int inf = 1e6;
struct Tag {
    int x;
    Tag(int _x) : x(_x) {}
    Tag() { x = 0; }
    void apply(const Tag &v) {
        x += v.x;
    }
};

struct Info {
    int mi[4];
    int cnt[4];
    Info(int x) {
        mi[0] = x;
        mi[1] = inf + 1, mi[2] = inf + 2, mi[3] = inf + 3;
        cnt[0] = 1;
        cnt[1] = cnt[2] = cnt[3] = 0;
    }

    Info() : mi{inf, inf + 1, inf + 2, inf + 3}, cnt{0, 0, 0, 0} {}

    void apply(const Tag &v) {
        for (int i = 0; i < 4; i++) {
            mi[i] += v.x;
        }
    }

    friend Info operator+(const Info &a, const Info &b) {
        int x = 0, y = 0;
        Info res;
        for (int i = 0; i < 4; i++) {
            // debug(x, y, a.mi[x], b.mi[y]);
            if (a.mi[x] < b.mi[y]) {
                res.mi[i] = a.mi[x];
                res.cnt[i] = a.cnt[x];
                x++;
            } else if (a.mi[x] > b.mi[y]) {
                res.mi[i] = b.mi[y];
                res.cnt[i] = b.cnt[y];
                y++;
            } else {
                res.mi[i] = a.mi[x];
                res.cnt[i] = a.cnt[x] + b.cnt[y];
                x++, y++;
            }
        }
        return res;
    }
};