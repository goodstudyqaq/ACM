#include <bits/stdc++.h>
#include <algorithm>

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

struct Tag {
    // 默认值
    int val;
    Tag(int _val = 0) {
        val = _val;
    }
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.val != 0) {
            val += v.val;
        }
    }
};

struct Info {
    // 默认值
    int mi, num;
    Info(int _mi = 0, int _num = 1) {
        mi = _mi;
        num = _num;
    }

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.val != 0) {
            mi += v.val;
        }
    }

    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        int tmp = min(left_info.mi, right_info.mi);
        int num = 0;
        if (tmp == left_info.mi) num += left_info.num;
        if (tmp == right_info.mi) num += right_info.num;
        return Info(tmp, num);
    }
};

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template <typename Info, typename Tag>
struct LazySegmentTree {
    LazySegmentTree(int n) : n(n), merge(Info::merge), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(vector<Info> &init) : LazySegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
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

    void update(int L, const Info &v) {
        update(L, v, 0, n - 1, 1);
    }

    void rangeUpdate(int L, int R, const Tag &v) {
        return rangeUpdate(L, R, v, 0, n - 1, 1);
    }

    Info rangeQuery(int L, int R) {
        return rangeQuery(L, R, 0, n - 1, 1);
    }

    int find_first(int ll, int rr, const function<bool(const Info &)> &f) {  // 找到第一个满足 f 的位置 idx, 使用这个函数的前提是在 [ll, idx - 1] 的任意区间都不满足 f,而对于任意 r，[ll, r], r >= idx 都满足 f。
        return find_first(ll, rr, f, 0, n - 1, 1);
    }

    int find_last(int ll, int rr, const function<bool(const Info &)> &f) {  // 从后往前找，找到第一个满足 f 的位置
        return find_last(ll, rr, f, 0, n - 1, 1);
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

    void update(int L, const Info &v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
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

    int find_first_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
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

    int find_first(int L, int R, const function<bool(const Info &)> f, int l, int r, int rt) {
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

    int find_last_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
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

    int find_last(int L, int R, const function<bool(const Info &)> f, int l, int r, int rt) {
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
};

void solve() {
    int n, m;
    cin >> n >> m;

    LazySegmentTree<Info, Tag> seg(n);  // [0, n - 1]
    for (int i = 0; i < n; i++) {
        seg.update(i, Info(0, 1));
    }
    vector<vector<int>> V(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        seg.rangeUpdate(a, b - 1, Tag(1));

        V[a].push_back(b);
        V[b].push_back(a);
    }

    auto tmp_res = seg.rangeQuery(0, n - 1);
    int ans = 0;
    ans = max(ans, tmp_res.num);


    for (int i = 0; i < n - 1; i++) {
        for (auto it : V[i]) {
            if (it > i) {
                // 删
                seg.rangeUpdate(i, it - 1, Tag(-1));
                if (i - 1 >= 0) {
                    seg.rangeUpdate(0, i - 1, Tag(1));
                }
                seg.rangeUpdate(it, n - 1, Tag(1));
            } else {
                // 加
                if (it - 1 >= 0) {
                    seg.rangeUpdate(0, it - 1, Tag(-1));
                }
                seg.rangeUpdate(i, n - 1, Tag(-1));
                seg.rangeUpdate(it, i - 1, Tag(1));
            }
        }
        auto tmp_res = seg.rangeQuery(0, n - 1);
        ans = max(ans, tmp_res.num);
    }
    cout << n - ans << endl;
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