#line 1 "D.cpp"
#include <bits/stdc++.h>

#line 4 "D.cpp"

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

    void assign(int L, const Info &v) {
        assign(L, v, 0, n - 1, 1);
    }

    void rangeUpdate(int L, int R, const Tag &v) {
        return rangeUpdate(L, R - 1, v, 0, n - 1, 1);
    }

    Info rangeQuery(int L, int R) {
        return rangeQuery(L, R - 1, 0, n - 1, 1);
    }

    int find_first(int ll, int rr, const function<bool(const Info &)> &f) {  // 找到第一个满足 f 的位置 idx, 使用这个函数的前提是在 [ll, idx - 1] 的任意区间都不满足 f,而对于任意 r，[ll, r], r >= idx 都满足 f。
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

#undef lson
#undef rson
};
#line 6 "D.cpp"

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
    long long num;
    Tag(long long num = -1) : num(num) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.num != -1) {
            num = v.num;
        }
    }
};

struct Info {
    // 默认值
    long long sum;
    Info(long long sum = 0) : sum(sum) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.num != -1) {
            sum = 1LL * (r - l + 1) * v.num;
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info(left_info.sum + right_info.sum);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    LazySegmentTree<Info, Tag> st(n);
    st.rangeUpdate(0, 1, Tag(a[0]));

    for (int i = 1; i < n; i++) {
        int l = 0, r = i - 1;
        int ans = -1;
        while (l <= r) {
            int m = l + r >> 1;
            long long avg = st.rangeQuery(m, i).sum + a[i];
            avg = avg / (i - m + 1);
            if (st.rangeQuery(m, m + 1).sum > avg) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        debug(i, ans);
        if (ans == -1) {
            st.rangeUpdate(i, i + 1, Tag(a[i]));
        } else {
            long long tmp = st.rangeQuery(ans, i).sum + a[i];
            long long avg = tmp / (i - ans + 1);
            long long more = tmp % (i - ans + 1);
            debug(avg, more);
            int len = i - ans + 1;
            int left = ans;
            int right = i - more;
            st.rangeUpdate(left, right + 1, Tag(avg));
            if (more > 0) {
                st.rangeUpdate(right + 1, i + 1, Tag(avg + 1));
            }
        }
    }

    long long mi = st.rangeQuery(0, 1).sum;
    long long mx = st.rangeQuery(n - 1, n).sum;
    for (int i = 1; i < n; i++) {
        long long it = st.rangeQuery(i, i + 1).sum;
        debug(i, it);
        mx = max(mx, it);
        mi = min(mi, it);
    }
    cout << mx - mi << endl;
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
