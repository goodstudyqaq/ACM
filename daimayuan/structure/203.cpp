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
    long long val = 0;
    Tag(long long val = 0) : val(val) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.val) {
            val += v.val;
        }
    }
};

struct Info {
    // 默认值
    long long mx = 0;
    Info(long long mx = 0) : mx(mx) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.val) {
            mx += v.val;
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info(max(left_info.mx, right_info.mx));
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
    LazySegmentTree<Info, Tag> seg(a);
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int l, r, d;
            cin >> l >> r >> d;
            l--, r--;
            seg.rangeUpdate(l, r + 1, Tag(d));
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << seg.rangeQuery(l, r + 1).mx << endl;
        }
    }
}
