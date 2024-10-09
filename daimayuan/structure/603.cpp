#include <bits/stdc++.h>

#include "./structure/segment-tree/lazy-segment-tree.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    Tag(int val = 0) : val(val) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.val) {
            val += v.val;
        }
    }
};

struct Info {
    // 默认值
    int mi;
    Info(int mi = 0) : mi(mi) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.val) {
            mi += v.val;
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info(min(left_info.mi, right_info.mi));
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<Info> dp(n + 1, Info(1e9));
    dp[0] = 0;
    for (int j = 1; j <= k; j++) {
        vector<int> pos(n + 1);
        LazySegmentTree<Info, Tag> seg(dp);
        vector<Info> ndp(n + 1);
        for (int i = 1; i <= n; i++) {
            int last = pos[a[i]];
            if (last != 0) {
                seg.rangeUpdate(0, last, Tag(i - last));
            }
            int res = seg.rangeQuery(0, i).mi;
            ndp[i] = res;
            pos[a[i]] = i;
        }
        dp = ndp;
    }
    cout << dp[n].mi << endl;
}