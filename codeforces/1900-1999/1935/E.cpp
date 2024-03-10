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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

/*
@brief 线段树
@docs docs/segment_tree.md
*/
struct Info {
    // 默认值
    int val;
    Info(int _v = 0) {
        val = _v;
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        Info ans;
        ans.val = left_info.val | right_info.val;
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

void solve() {
    int n;
    cin >> n;
    typedef pair<int, int> pii;
    vector<pii> V(n);
    vector<int> w(n);

    auto work = [&](int idx, int x, int y) {
        int tmp = (1 << (__lg(x ^ y) + 1)) - 1;
        int tmp2 = x - (x & tmp);
        w[idx] = tmp2;
        return pii(x - tmp2, y - tmp2);
    };

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        V[i] = work(i, x, y);
    }

    SegmentTree<Info> seg(n);
    for (int i = 0; i < n; i++) {
        seg.assign(i, w[i]);
    }

    vector<vector<int>> bits(30, vector<int>(n));
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < n; j++) {
            bits[i][j] = (V[j].second >> i) & 1;
            if (j > 0) {
                bits[i][j] += bits[i][j - 1];
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        Info tmp = seg.rangeQuery(l, r);
        int val = tmp.val;
        int ans = tmp.val;
        for (int i = 29; i >= 0; i--) {
            int cnt = bits[i][r];
            if (l > 0) cnt -= bits[i][l - 1];
            cnt += (val >> i) & 1;
            if (cnt == 0) {
                continue;
            } else if (cnt == 1) {
                ans |= (1 << i);
            } else {
                ans |= ((2 << i) - 1);
                break;
            }
        }
        cout << ans << ' ';
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
    return 0;
}
