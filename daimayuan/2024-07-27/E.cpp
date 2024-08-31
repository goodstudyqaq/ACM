#include <bits/stdc++.h>

#include "./math/mint.hpp"
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

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

struct Tag {
    // 默认值
    Mint a, c;
    Tag(Mint a = 1, Mint c = 0) : a(a), c(c) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag& v, int l, int r) {
        Mint a2 = a * v.a;
        Mint c2 = v.a * c + v.c;
        a = a2;
        c = c2;
    }
};

struct Info {
    // 默认值
    Mint sum;
    Info(Mint sum = 0) : sum(sum) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag& v, int l, int r) {
        sum = sum * v.a + Mint(r - l + 1) * v.c;
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info(left_info.sum + right_info.sum);
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    LazySegmentTree<Info, Tag> st(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        st.assign(i, Info(a[i]));
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            st.rangeUpdate(l, r, Tag(b, c));
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.rangeQuery(l, r).sum << endl;
        }
    }
    return 0;
}