#line 1 "H.cpp"
#include <bits/stdc++.h>

#line 4 "H.cpp"

#line 2 "/Users/guoshen/code/library2/structure/segment-tree/lazy-segment-tree.hpp"
using namespace std;

/*
struct Tag {
    // 默认值
    Tag() {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
    }
};

struct Info {
    // 默认值
    Info() {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info();
    }
};
*/

template <typename Info, typename Tag>
struct LazySegmentTree {
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
    LazySegmentTree(int n) : n(n), merge(Info::merge), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(vector<Info> &init) : LazySegmentTree(init.size()) {
        initSegmentTree(init);
    }

    void initSegmentTree(vector<Info> &init) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
            tag[rt] = Tag();
            if (l == r) {
                info[rt] = init[l];
                return;
            }
            int m = l + r >> 1;
            build(lson);
            build(rson);
            push_up(l, r, rt);
        };
        build(0, n - 1, 1);
    }

    void assign(int L, const Info &v) {
        assign(L, v, 0, n - 1, 1);
    }

    void rangeUpdate(int L, int R, const Tag &v) {
        return rangeUpdate(L, R - 1, v, 0, n - 1, 1);
    }

    Info rangeQuery(int L, int R) {
        return rangeQuery(L, R - 1, 0, n - 1, 1);
    }

    int find_first(int ll, int rr, const function<bool(const Info &)> &f) {  // 找到第一个满足 f 的位置 idx, 可以理解在原数组中[ll, idx - 1] 都不满足 f
        return find_first(ll, rr - 1, f, 0, n - 1, 1);
    }

    int find_last(int ll, int rr, const function<bool(const Info &)> &f) {  // 从后往前找，找到第一个满足 f 的位置
        return find_last(ll, rr - 1, f, 0, n - 1, 1);
    }

   private:
    const int n;
    vector<Info> info;
    vector<Tag> tag;
    const function<Info(const Info &, const Info &, int, int)> merge;
    void push_up(int l, int r, int rt) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1], l, r);
    }

    void apply(int p, const Tag &v, int l, int r) {
        info[p].apply(v, l, r);
        tag[p].apply(v, l, r);
    }

    void push_down(int l, int r, int rt) {
        int m = l + r >> 1;
        apply(rt << 1, tag[rt], l, m);
        apply(rt << 1 | 1, tag[rt], m + 1, r);
        tag[rt] = Tag();
    }

    void assign(int L, const Info &v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m) {
            assign(L, v, lson);
        } else {
            assign(L, v, rson);
        }
        push_up(l, r, rt);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson), l, r);
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void rangeUpdate(int L, int R, const Tag &v, int l, int r, int rt) {
        if (L <= l && r <= R) {
            apply(rt, v, l, r);
            return;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m) {
            rangeUpdate(L, R, v, lson);
        }
        if (R > m) {
            rangeUpdate(L, R, v, rson);
        }
        push_up(l, r, rt);
    }

    int find_first_knowingly(const function<bool(const Info &)> &f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res;
        if (f(info[rt << 1])) {
            res = find_first_knowingly(f, lson);
        } else {
            res = find_first_knowingly(f, rson);
        }
        push_up(l, r, rt);
        return res;
    }

    int find_first(int L, int R, const function<bool(const Info &)> &f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_first_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res = -1;
        if (L <= m) {
            res = find_first(L, R, f, lson);
        }
        if (R > m && res == -1) {
            res = find_first(L, R, f, rson);
        }
        push_up(l, r, rt);
        return res;
    }

    int find_last_knowingly(const function<bool(const Info &)> &f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res;
        if (f(info[rt << 1 | 1])) {
            res = find_last_knowingly(f, rson);
        } else {
            res = find_last_knowingly(f, lson);
        }
        push_up(l, r, rt);
        return res;
    }

    int find_last(int L, int R, const function<bool(const Info &)> &f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_last_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res = -1;
        if (R > m) {
            res = find_last(L, R, f, rson);
        }
        if (L <= m && res == -1) {
            res = find_last(L, R, f, lson);
        }
        push_up(l, r, rt);
        return res;
    }

#undef lson
#undef rson
};
#line 6 "H.cpp"

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

// 区间加 + 区间赋值
struct Tag {
    // 默认值
    int flag1;  // 区间加
    int flag2;  // 区间赋值
    int val;
    Tag(int flag1 = 0, int flag2 = 0, int val = 0) : flag1(flag1), flag2(flag2), val(val) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.flag2) {
            flag2 = 1;
            val = v.val;
            flag1 = 0;
        } else if (v.flag1) {
            if (flag1 || flag2) {
                val += v.val;
            } else {
                val = v.val;
                flag1 = 1;
            }
        }
    }
};

struct Info {
    // 默认值
    int mx;
    Info(int mx = 0) : mx(mx) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.flag1) {
            mx += v.val;
        } else if (v.flag2) {
            mx = v.val;
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info(max(left_info.mx, right_info.mx));
    }
};

void solve() {
    int n;
    cin >> n;
    vector<pii> p(n);
    vector<int> X;
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        X.push_back(p[i].first);
        X.push_back(p[i].second);
    }
    sort(X.begin(), X.end());
    X.resize(unique(X.begin(), X.end()) - X.begin());

    int sz = X.size();
    LazySegmentTree<Info, Tag> seg(sz);

    // vector<Info> init(sz);
    // seg.initSegmentTree(init);

    for (int i = 0; i < n; i++) {
        auto [l, r] = p[i];

        int idx1 = lower_bound(X.begin(), X.end(), l) - X.begin();
        int idx2 = lower_bound(X.begin(), X.end(), r) - X.begin();
        seg.rangeUpdate(idx1, idx2 + 1, Tag(1, 0, 1));
        int mx1 = seg.rangeQuery(0, idx2 + 1).mx;
        // debug(i, mx1, idx1, idx2);
        int tmp_idx = lower_bound(X.begin(), X.end(), 4) - X.begin();
        // debug(seg.rangeQuery(tmp_idx, tmp_idx + 1).mx);

        int L = idx2 + 1, R = sz - 1;
        if (L <= R) {
            // debug(L, R);
            const function<bool(const Info &)> &f = [&](const Info &info) -> bool {
                return info.mx >= mx1;
            };
            int ans = seg.find_first(idx2 + 1, sz, f);

            // debug(ans);
            if (ans != -1) {
                seg.rangeUpdate(idx2 + 1, ans, Tag(0, 1, mx1));
            } else {
                seg.rangeUpdate(idx2 + 1, sz, Tag(0, 1, mx1));
            }
        }

        cout << seg.rangeQuery(0, sz).mx << ' ';
    }
    cout << '\n';
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
