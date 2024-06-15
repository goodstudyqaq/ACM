#include <bits/stdc++.h>

#include <algorithm>

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

/*
@brief Lazy Segment Tree
@docs docs/lazy_segment_tree.md
*/

/*
 */
struct Tag {
    // 默认值
    Tag() {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {}
};

struct Info {
    // 默认值
    int mi;
    Info(int _mi = 1e9) {
        mi = _mi;
    }

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        return;
    }

    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        Info res;
        res.mi = min(left_info.mi, right_info.mi);
        return res;
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
    string s;
    cin >> s;
    int n = s.size();
    vector<int> V(n + 1);
    vector<int> revV(n + 1);
    map<int, vector<int>> M;
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '(') {
            V[i] = 1;
        } else {
            V[i] = -1;
        }
        revV[i] = V[i] * -1;
    }
    // debug(V);

    vector<int> sumrevV(n + 1);
    for (int i = 1; i <= n; i++) {
        sumrevV[i] = sumrevV[i - 1] + revV[i];
        M[sumrevV[i]].push_back(i);
    }
    debug(sumrevV);
    LazySegmentTree<Info, Tag> seg(n + 1);
    for (int i = 1; i <= n; i++) {
        seg.update(i, Info(sumrevV[i]));
    }
    int now = 0;
    long long ans = 0;
    for (int i = 1; i < n; i++) {
        if (now > 0) {
            int tmp2 = sumrevV[i - 1];
            int idx = seg.find_first(i, n, [&](const Info &info) {
                return info.mi < -now + tmp2;
            });
            debug(i, idx);

            int tmp = sumrevV[i - 1];
            if (idx != -1) {
                int idx2 = lower_bound(M[tmp].begin(), M[tmp].end(), idx) - M[tmp].begin();
                int idx3 = lower_bound(M[tmp].begin(), M[tmp].end(), i - 1) - M[tmp].begin();
                debug(i, idx, idx2, idx3);
                ans += idx2 - idx3 - 1;
            } else {
                int idx3 = lower_bound(M[tmp].begin(), M[tmp].end(), i - 1) - M[tmp].begin();
                debug(i, tmp, idx3);
                ans += M[tmp].size() - idx3 - 1;
            }
            debug(ans);
        }
        now += V[i];
    }
    cout << ans << endl;
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