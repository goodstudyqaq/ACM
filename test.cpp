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
    int mx = 0;
    Info(int mx = 0) : mx(mx) {}
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
    int n = 20;
    SegmentTree<Info> seg(n);
    seg.assign(10, Info(20));
    auto res = seg.rangeQuery(0, 10);
    cout << res.mx << endl;
}