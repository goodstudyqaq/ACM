#include <bits/stdc++.h>

#include "./structure/segment-tree/segment-tree.hpp"

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
struct Info {
    // 默认值
    int mx = -1;
    Info(int mx = -1) : mx(mx) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info(max(left_info.mx, right_info.mx));
    }
    string to_string() {
        return "";
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int N, D, R;
    cin >> N >> D >> R;

    vector<int> h(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> h[i];
    }
    SegmentTree<Info> seg(N + 1);
    vector<int> f(N + 1);
    iota(f.begin() + 1, f.begin() + 1 + N, 1);

    sort(f.begin() + 1, f.begin() + 1 + N, [&](int x, int y) {
        return h[x] < h[y];
    });

    int ans = 0;
    vector<int> dp(N + 1);
    for (int i = 1; i <= N; i++) {
        int idx = f[i];
        int l = max(1, idx - R);
        int r = min(N, idx + R);

        auto it = seg.rangeQuery(l, r + 1);
        dp[idx] = it.mx + 1;
        ans = max(ans, it.mx + 1);
        debug(idx, ans);
        if (i >= D) {
            idx = f[i - D + 1];
            seg.assign(idx, dp[idx]);
        }
    }
    cout << ans << '\n';
}