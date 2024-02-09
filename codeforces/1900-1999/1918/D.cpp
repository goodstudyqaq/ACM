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
    long long s;
    Info(long long _s = 0) {
        s = _s;
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        long long res = min(left_info.s, right_info.s);
        Info ans;
        ans.s = res;
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
    vector<int> a(n + 1);
    vector<long long> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = a[i] + sum[i - 1];
    }
    long long l = 0, r = sum[n];
    long long ans = -1;
    vector<long long> dp(n + 1);

    auto check = [&](long long val) {
        vector<Info> infos(n + 1);
        SegmentTree<Info> segs(infos);
        for (int i = 1; i <= n; i++) {
            if (val < a[i]) return false;
            long long s1 = sum[i - 1];
            if (s1 <= val) {
                // 可以全都算
                // debug(i, "all");
                Info it = segs.rangeQuery(0, i - 1);
                dp[i] = a[i] + it.s;
                segs.assign(i, Info(dp[i]));
            } else {
                long long k = s1 - val;
                int idx = lower_bound(sum.begin(), sum.begin() + 1 + i, k) - sum.begin();
                Info it = segs.rangeQuery(idx, i - 1);
                // debug(i, idx, it.s);
                dp[i] = a[i] + it.s;
                segs.assign(i, Info(dp[i]));
            }
        }
        // debug(dp);

        for (int i = 1; i <= n; i++) {
            long long tmp = max(dp[i], sum[n] - sum[i]);
            if (tmp <= val) return true;
        }
        return false;
    };
    // l = r = 5;
    while (l <= r) {
        long long m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
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