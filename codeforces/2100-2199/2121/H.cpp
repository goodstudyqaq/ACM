#include <bits/stdc++.h>

#include <algorithm>

#include "./structure/segment-tree/lazy-segment-tree.hpp"

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

// 区间加 + 区间赋值
struct Tag {
    // 默认值
    int flag1;  // 区间加
    int flag2;  // 区间赋值
    int val;
    Tag(int flag1 = 0, int flag2 = 0, int val = 0) : flag1(flag1), flag2(flag2), val(val) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.flag2) {
            flag2 = 1;
            val = v.val;
            flag1 = 0;
        } else if (v.flag1) {
            if (flag1 || flag2) {
                val += v.val;
            } else {
                val = v.val;
                flag1 = 1;
            }
        }
    }
};

struct Info {
    // 默认值
    int mx;
    Info(int mx = 0) : mx(mx) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.flag1) {
            mx += v.val;
        } else if (v.flag2) {
            mx = v.val;
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info(max(left_info.mx, right_info.mx));
    }
};

void solve() {
    int n;
    cin >> n;
    vector<pii> p(n);
    vector<int> X;
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        X.push_back(p[i].first);
        X.push_back(p[i].second);
    }
    sort(X.begin(), X.end());
    X.resize(unique(X.begin(), X.end()) - X.begin());

    int sz = X.size();
    LazySegmentTree<Info, Tag> seg(sz);

    // vector<Info> init(sz);
    // seg.initSegmentTree(init);

    for (int i = 0; i < n; i++) {
        auto [l, r] = p[i];

        int idx1 = lower_bound(X.begin(), X.end(), l) - X.begin();
        int idx2 = lower_bound(X.begin(), X.end(), r) - X.begin();
        seg.rangeUpdate(idx1, idx2 + 1, Tag(1, 0, 1));
        int mx1 = seg.rangeQuery(0, idx2 + 1).mx;
        // debug(i, mx1, idx1, idx2);
        int tmp_idx = lower_bound(X.begin(), X.end(), 4) - X.begin();
        // debug(seg.rangeQuery(tmp_idx, tmp_idx + 1).mx);

        int L = idx2 + 1, R = sz - 1;
        if (L <= R) {
            // debug(L, R);
            const function<bool(const Info &)> &f = [&](const Info &info) -> bool {
                return info.mx >= mx1;
            };
            int ans = seg.find_first(idx2 + 1, sz, f);

            // debug(ans);
            if (ans != -1) {
                seg.rangeUpdate(idx2 + 1, ans, Tag(0, 1, mx1));
            } else {
                seg.rangeUpdate(idx2 + 1, sz, Tag(0, 1, mx1));
            }
        }

        cout << seg.rangeQuery(0, sz).mx << ' ';
    }
    cout << '\n';
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