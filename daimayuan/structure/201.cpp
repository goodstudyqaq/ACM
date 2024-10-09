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
    int mi, num;
    Info(int mi = 0, int num = 0) : mi(mi), num(num) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int mi = min(left_info.mi, right_info.mi);
        int num = 0;
        if (mi == left_info.mi) num += left_info.num;
        if (mi == right_info.mi) num += right_info.num;
        return {mi, num};
    }
    string to_string() {
        return "";
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;
    vector<Info> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].mi;
        a[i].num = 1;
    }
    SegmentTree<Info> seg(a);
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, d;
            cin >> x >> d;
            x--;
            seg.assign(x, Info(d, 1));
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            auto res = seg.rangeQuery(l, r + 1);
            cout << res.mi << ' ' << res.num << endl;
        }
    }
}