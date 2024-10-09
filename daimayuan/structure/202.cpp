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
    long long left_mx, right_mx, mx, sum;

    Info(long long lmx = 0, long long rmx = 0, long long mx = 0, long long sum = 0) : left_mx(lmx), right_mx(rmx), mx(mx), sum(sum) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        long long left_mx = max(left_info.left_mx, left_info.sum + right_info.left_mx);
        long long right_mx = max(right_info.right_mx, right_info.sum + left_info.right_mx);
        long long mx = max({left_info.mx, right_info.mx, left_info.right_mx + right_info.left_mx});
        long long sum = left_info.sum + right_info.sum;
        return {left_mx, right_mx, mx, sum};
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
        int x;
        cin >> x;
        a[i] = Info(x, x, x, x);
    }
    SegmentTree<Info> seg(a);
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, d;
            cin >> x >> d;
            x--;
            seg.assign(x, Info(d, d, d, d));
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            auto res = seg.rangeQuery(l, r + 1);
            cout << res.mx << endl;
        }
    }
}