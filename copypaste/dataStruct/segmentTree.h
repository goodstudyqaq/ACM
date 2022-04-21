#include <bits/stdc++.h>
using namespace std;

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
};

const int inf = (1 << 30) - 1;
struct Info {
    int v[31];
    Info(int x = inf) {
        v[0] = x;
        for (int i = 1; i < 31; i++) {
            v[i] = inf;
        }
    }
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    int i = 0, j = 0;
    while (i + j < 31) {
        if (a.v[i] < b.v[j]) {
            c.v[i + j] = a.v[i];
            i++;
        } else {
            c.v[i + j] = b.v[j];
            j++;
        }
    }
    return c;
}