#include <bits/stdc++.h>

#include <queue>

#include "./structure/segment-tree/segment-tree.hpp"

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
const int inf = 1e9 + 1;
struct Info {
    // 默认值
    int mx_idx, mi_idx;
    int mx_val, mi_val;
    Info(int mx_val = -1, int mi_val = inf, int mx_idx = 0, int mi_idx = 0) : mx_val(mx_val), mi_val(mi_val), mx_idx(mx_idx), mi_idx(mi_idx) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int mx_val = max(left_info.mx_val, right_info.mx_val);
        int mi_val = min(left_info.mi_val, right_info.mi_val);
        int mx_idx = mx_val == left_info.mx_val ? left_info.mx_idx : right_info.mx_idx;
        int mi_idx = mi_val == right_info.mi_val ? right_info.mi_idx : left_info.mi_idx;
        return Info(mx_val, mi_val, mx_idx, mi_idx);
    }
    string to_string() {
        return "";
    }
};

void solve() {
    int n;
    cin >> n;
    int N = n * 2;
    vector<int> a(N);
    vector<Info> infos(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        infos[i] = Info{a[i], a[i], i, i};
    }
    SegmentTree<Info> seg(infos);

    int times = n;
    long long ans = 0;
    while (times--) {
        auto it = seg.rangeQuery(0, N);
        int idx1 = it.mx_idx;
        auto it2 = seg.rangeQuery(idx1 + 1, N);
        if (it2.mi_val == inf) {
            // 没有值
            it = seg.rangeQuery(0, idx1);
            idx1 = it.mx_idx;
            it2 = seg.rangeQuery(idx1 + 1, N);
        }
        debug(idx1);
        ans += it.mx_val;
        seg.assign(idx1, Info{});
        seg.assign(it2.mi_idx, Info{});
    }
    cout << ans << '\n';
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