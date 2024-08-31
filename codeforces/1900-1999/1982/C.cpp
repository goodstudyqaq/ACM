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
struct Info {
    // 默认值
    int mx;
    Info(int _mx = 0) {
        mx = _mx;
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        Info res;
        res.mx = max(left_info.mx, right_info.mx);
        return res;
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
    int n, l, r;
    cin >> n >> l >> r;
    vector<long long> a(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = a[i];
        if (i) sum[i] += sum[i - 1];
    }
    SegmentTree<Info> seg(n + 1);

    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        long long now_sum = sum[i];
        if (now_sum < l) {
            dp[i] = 0;
            seg.assign(i, Info(dp[i]));
            continue;
        }
        int now_a = a[i];
        if (a[i] > r) {
            dp[i] = dp[i - 1];
            seg.assign(i, Info(dp[i]));
            continue;
        }

        long long tmp1 = now_sum - l;
        long long tmp2 = now_sum - r;

        // 大于等于 tmp2 小于等于 tmp1

        int it1 = lower_bound(sum.begin(), sum.begin() + i, tmp2) - sum.begin();
        int it2 = upper_bound(sum.begin(), sum.begin() + i, tmp1) - sum.begin();

        // [it1, it2)

        if (it2 == it1) {
            // 没有
            dp[i] = dp[i - 1];
        } else {
            int v1 = seg.rangeQuery(it1, it2 - 1).mx + 1;
            int v2 = it1 > 0 ? seg.rangeQuery(0, it1 - 1).mx : 0;
            int v3 = seg.rangeQuery(it2, i).mx;
            dp[i] = max({v1, v2, v3});
        }
        seg.assign(i, Info(dp[i]));
    }
    debug(dp);
    cout << dp[n] << endl;
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