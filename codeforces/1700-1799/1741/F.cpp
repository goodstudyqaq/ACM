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
typedef array<int, 4> a4;

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
    Tag() {
        val = 0;
    }
    Tag(int _v) : val(_v) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.val != 0) {
            val += v.val;
        }
    }
};

struct Info {
    // 默认值

    int mx;

    Info() { mx = 0; }
    Info(int _mx) : mx(_mx) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.val != 0) {
            mx += v.val;
        }
    }

    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        int mx = max(left_info.mx, right_info.mx);
        return Info(mx);
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
            push_up(rt, l, r);
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
    int n;
    cin >> n;
    vector<a4> V(n);
    vector<int> x(2 * n);
    int x_cnt = 0;
    vector<vector<int>> V2(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> V[i][0] >> V[i][1] >> V[i][2];
        V[i][3] = i;
        x[x_cnt++] = V[i][0];
        x[x_cnt++] = V[i][1];
        V2[V[i][2]].push_back(i);
    }
    sort(x.begin(), x.begin() + x_cnt);
    x_cnt = unique(x.begin(), x.end()) - x.begin();
    x.resize(x_cnt);

    LazySegmentTree<Info, Tag> seg(x_cnt);

    multiset<int> left, right;
    for (int i = 0; i < n; i++) {
        V[i][0] = lower_bound(x.begin(), x.begin() + x_cnt, V[i][0]) - x.begin();
        V[i][1] = lower_bound(x.begin(), x.begin() + x_cnt, V[i][1]) - x.begin();
        seg.rangeUpdate(V[i][0], V[i][1], Tag(1));
        left.insert(x[V[i][0]]);
        right.insert(x[V[i][1]]);
    }
    const int inf = numeric_limits<int>::max() / 2;
    vector<int> ans(n + 1, inf);

    for (int i = 1; i <= n; i++) {
        if (V2[i].size()) {
            // 先删掉
            for (auto idx : V2[i]) {
                auto it = V[idx];
                int L = it[0];
                int R = it[1];
                seg.rangeUpdate(L, R, Tag(-1));
                left.erase(left.find(x[L]));
                right.erase(right.find(x[R]));
            }

            for (auto idx : V2[i]) {
                auto it = V[idx];
                int L = it[0];
                int R = it[1];
                Info it2 = seg.rangeQuery(L, R);
                if (it2.mx >= 1) {
                    ans[it[3]] = 0;
                } else {
                    auto it1 = left.lower_bound(x[R]);
                    if (it1 != left.end()) {
                        ans[it[3]] = min(ans[it[3]], *it1 - x[R]);
                    }
                    auto it2 = right.lower_bound(x[L]);
                    if (it2 != right.begin()) {
                        it2--;
                        ans[it[3]] = min(ans[it[3]], x[L] - *it2);
                    }
                }
            }

            // 加回来
            for (auto idx : V2[i]) {
                auto it = V[idx];
                int L = it[0];
                int R = it[1];
                seg.rangeUpdate(L, R, Tag(1));
                left.insert(x[L]);
                right.insert(x[R]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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
}