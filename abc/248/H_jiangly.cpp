#include <bits/stdc++.h>

using i64 = long long;

template <class Info, class Tag,
          class Merge = std::plus<Info>>
struct LazySegmentTree {
    const int n;
    const Merge merge;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
};

constexpr int inf = 1E9;

struct Tag {
    int x;
    Tag(int x = 0) : x(x) {}
    void apply(const Tag &a) {
        x += a.x;
    }
};

struct Info {
    int min[4];
    int cnt[4];
    Info() : min{inf, inf + 1, inf + 2, inf + 3}, cnt{0, 0, 0, 0} {}
    Info(int x) : min{x, inf, inf + 1, inf + 2}, cnt{1, 0, 0, 0} {}
    void apply(const Tag &a) {
        for (int i = 0; i < 4; i++) {
            min[i] += a.x;
        }
    }
    friend Info operator+(const Info &a, const Info &b) {
        Info c;
        int x = 0, y = 0;
        for (int i = 0; i < 4; i++) {
            if (a.min[x] < b.min[y]) {
                c.min[i] = a.min[x];
                c.cnt[i] = a.cnt[x];
                x++;
            } else if (a.min[x] > b.min[y]) {
                c.min[i] = b.min[y];
                c.cnt[i] = b.cnt[y];
                y++;
            } else {
                c.min[i] = b.min[y];
                c.cnt[i] = a.cnt[x] + b.cnt[y];
                x++;
                y++;
            }
        }
        return c;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }

    LazySegmentTree<Info, Tag> seg(n);

    i64 ans = 0;
    std::vector<int> smax{-1}, smin{-1};
    for (int i = 0; i < n; i++) {
        while (smax.size() > 1 && p[i] > p[smax.back()]) {
            int x = smax.back();
            smax.pop_back();
            seg.rangeApply(smax.back() + 1, x + 1, p[i] - p[x]);
        }
        while (smin.size() > 1 && p[i] < p[smin.back()]) {
            int x = smin.back();
            smin.pop_back();
            seg.rangeApply(smin.back() + 1, x + 1, -(p[i] - p[x]));
        }
        smax.push_back(i);
        smin.push_back(i);
        seg.rangeApply(0, n, -1);
        seg.modify(i, Info(0));
        for (int j = 0; j <= k; j++) {
            if (seg.info[1].min[j] <= k) {
                ans += seg.info[1].cnt[j];
            }
        }
    }

    std::cout << ans << "\n";

    return 0;
}