#include <bits/stdc++.h>

#include <algorithm>

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
struct Info1 {
    // 默认值
    int mi, num;
    Info1(int _mi = 1e9 + 1, int _num = 1) {
        mi = _mi;
        num = _num;
    }
    static Info1 merge(const Info1& left_info, const Info1& right_info, int l, int r) {
        Info1 ans;
        ans.mi = min(left_info.mi, right_info.mi);
        ans.num = 0;
        if (ans.mi == left_info.mi) ans.num += left_info.num;
        if (ans.mi == right_info.mi) ans.num += right_info.num;
        return ans;
    };
};
struct Info2 {
    // 默认值
    int g;
    Info2(int _g = 0) {
        g = _g;
    }
    static Info2 merge(const Info2& left_info, const Info2& right_info, int l, int r) {
        Info2 ans;
        ans.g = __gcd(left_info.g, right_info.g);
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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegmentTree<Info1> seg1(n);
    SegmentTree<Info2> seg2(n);

    for (int i = 0; i < n; i++) {
        seg1.assign(i, Info1(a[i]));
        seg2.assign(i, Info2(a[i]));
    }

    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int all = r - l + 1;
        auto it = seg1.rangeQuery(l, r);
        auto it2 = seg2.rangeQuery(l, r);

        if (it.mi != it2.g) {
            cout << all << endl;
        } else {
            cout << all - it.num << endl;
        }
    }
    return 0;
}