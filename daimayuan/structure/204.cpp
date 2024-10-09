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
const int mod = 1e9 + 7;

struct Tag {
    // 默认值
    long long x = 1, y = 0;
    Tag(long long x = 1, long long y = 0) : x(x), y(y) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.x != 1 || v.y != 0) {
            // (p * x + y) * v.x + v.y
            long long x1 = x * v.x % mod;
            long long y1 = (y * v.x % mod + v.y) % mod;
            x = x1, y = y1;
        }
    }
};

struct Info {
    // 默认值
    long long sum = 0;
    Info(long long sum = 0) : sum(sum) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.x != 1 || v.y != 0) {
            sum = (sum * v.x % mod + 1LL * (r - l + 1) * v.y % mod) % mod;
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info((left_info.sum + right_info.sum) % mod);
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
        cin >> a[i].sum;
    }
    LazySegmentTree<Info, Tag> seg(a);
    while (q--) {
        int ty;
        cin >> ty;
        if (ty <= 3) {
            int l, r, d;
            cin >> l >> r >> d;
            l--, r--;
            if (ty == 1) {
                seg.rangeUpdate(l, r + 1, Tag(1, d));
            } else if (ty == 2) {
                seg.rangeUpdate(l, r + 1, Tag(d, 0));
            } else {
                seg.rangeUpdate(l, r + 1, Tag(0, d));
            }
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << seg.rangeQuery(l, r + 1).sum << endl;
        }
    }
}
