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

    int n, q;
    cin >> n >> q;
    vector<Info> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].mx;
    }
    SegmentTree<Info> seg(a);
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, d;
            cin >> x >> d;
            x--;
            seg.assign(x, Info(d));
        } else {
            int l, r, d;
            cin >> l >> r >> d;
            l--, r--;
            auto f = [&](const Info& info) {
                return info.mx >= d;
            };
            int res = seg.find_first(l, r + 1, f);
            if (res != -1) res++;
            cout << res << endl;
        }
    }
}