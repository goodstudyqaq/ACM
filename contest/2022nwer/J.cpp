#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

struct Info {
    // 默认值
    int val;
    Info(int _val = 0) {
        val = _val;
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        Info ans;
        ans.val = max(left_info.val, right_info.val);
        return ans;
    };
};

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template <typename Info>
struct SegmentTree {
    SegmentTree(int n) : n(n), merge(Info::merge), info(4 << __lg(n)) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size()) {
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

    Info rangeQuery(int l, int r) {
        return rangeQuery(l, r, 0, n - 1, 1);
    }

    // 单点更新, 会将下标为 L 的点与 v 进行 merge 操作
    void update(int L, const Info& v) {
        return update(L, v, 0, n - 1, 1);
    }

    // 单点赋值, 会将下标为 L 的点直接赋值为 v
    void assign(int L, const Info& v) {
        return assign(L, v, 0, n - 1, 1);
    }

   private:
    const int n;
    vector<Info> info;
    const function<Info(const Info&, const Info&, int, int)> merge;

    void push_up(int rt, int l, int r) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1], l, r);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson), l, r);
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void update(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = merge(info[rt], v, l, r);
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
        }
        push_up(rt, l, r);
    }

    void assign(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            assign(L, v, lson);
        } else {
            assign(L, v, rson);
        }
        push_up(rt, l, r);
    }
};
struct node {
    int time, flag, idx, r;
    bool operator<(const node& b) {
        if (time != b.time) {
            return time < b.time;
        }
        if (flag != b.flag) {
            return flag < b.flag;
        }
        return r > b.r;
    }
};
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;

    vector<node> v;
    typedef pair<int, int> pii;
    vector<pii> x;
    vector<pii> V(n);
    for (int i = 0; i < n; i++) {
        int a, t;
        cin >> a >> t;
        V[i] = {a, t};
        x.push_back({a, i});
        x.push_back({a + t, i});
        v.push_back((node){a, 1, i, a + t});
        v.push_back((node){a + t, -1, i, a + t});
    }
    sort(v.begin(), v.end());
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());

    int sz = x.size();
    SegmentTree<Info> seg(sz);
    vector<int> ans(n);
    for (int i = 0; i < v.size(); i++) {
        auto it = v[i];
        int t = it.time;
        int idx = it.idx;
        debug(t, idx, it.flag);
        if (it.flag == -1) {
            int the_idx = lower_bound(x.begin(), x.end(), pii(t, idx)) - x.begin();
            seg.assign(the_idx, Info(0));
        } else {
            int r = V[idx].first + V[idx].second;
            int tmp = lower_bound(x.begin(), x.end(), pii(r, -1)) - x.begin();
            auto it2 = seg.rangeQuery(tmp, sz - 1);
            ans[idx] = it2.val + 1;
            seg.assign(tmp, Info(ans[idx]));
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] - 1;
        if (i != n - 1) {
            cout << ' ';
        } else {
            cout << endl;
        }
    }
    return 0;
}