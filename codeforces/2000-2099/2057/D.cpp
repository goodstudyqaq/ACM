#include <bits/stdc++.h>

#include <algorithm>

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

struct Info {
    // 默认值
    int mi, mx, ans;
    Info(int mi = 0, int mx = 0, int ans = 0) : mi(mi), mx(mx), ans(ans) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int mi = min(left_info.mi, right_info.mi);
        int mx = max(left_info.mx, right_info.mx);
        int ans = max({left_info.ans, right_info.ans, right_info.mx - left_info.mi});
        return Info{mi, mx, ans};
    }
    string to_string() {
        return "";
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        infos[i] = Info{a[i] - i, a[i] - i, 0};
    }
    SegmentTree<Info> seg(infos);

    for (int i = 0; i < n; i++) {
        infos[i] = Info{a[n - 1 - i] - i, a[n - 1 - i] - i, 0};
    }
    SegmentTree<Info> seg2(infos);

    cout << max(seg.rangeQuery(0, n).ans, seg2.rangeQuery(0, n).ans) << '\n';

    for (int i = 0; i < q; i++) {
        int p, x;
        cin >> p >> x;
        p--;
        seg.assign(p, Info{x - p, x - p, 0});
        seg2.assign(n - 1 - p, Info{x - (n - 1 - p), x - (n - 1 - p), 0});
        cout << max(seg.rangeQuery(0, n).ans, seg2.rangeQuery(0, n).ans) << '\n';
        // auto tmp = seg2.rangeQuery(0, n);
        // auto tmp2 = seg2.rangeQuery(0, 1);
        // debug(tmp.mi, tmp.mx, tmp2.mi, tmp2.mx);
    }
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