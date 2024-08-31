#include <bits/stdc++.h>

#include <string>

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
    int left_mx, right_mx, mx, sum;
    Info(int left_mx = 0, int right_mx = 0, int mx = 0, int sum = 0) : left_mx(left_mx), right_mx(right_mx), mx(mx), sum(sum) {
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int left_mx = max(left_info.left_mx, left_info.sum + right_info.left_mx);
        int right_mx = max(right_info.right_mx, left_info.right_mx + right_info.sum);
        int mx = max({left_mx,
                      right_mx,
                      left_info.right_mx,
                      right_info.left_mx,
                      left_info.right_mx + right_info.left_mx});
        int sum = left_info.sum + right_info.sum;
        return Info(left_mx, right_mx, mx, sum);
    };
    string to_string() {
        return std::to_string(mx);
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> a(n);
    SegmentTree<Info> seg(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        seg.assign(i, Info(a[i], a[i], a[i], a[i]));
    }

    int m;
    cin >> m;
    while (m--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 0) {
            x--;
            seg.assign(x, Info(y, y, y, y));
        } else {
            x--, y--;
            cout << seg.rangeQuery(x, y + 1).mx << endl;
        }
    }
    return 0;
}