#include <bits/stdc++.h>

#include "./graph/tree/heavy-light-decomposition.hpp"
#include "./math/mint.hpp"
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

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

struct Info {
    // 默认值
    Mint a1, b1;
    Mint a2, b2;
    Info(Mint a1 = 1, Mint b1 = 0, Mint a2 = 1, Mint b2 = 0) : a1(a1), b1(b1), a2(a2), b2(b2) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        // a1, b1 -> left_info(right_info)
        Mint a1 = left_info.a1 * right_info.a1;
        Mint b1 = left_info.a1 * right_info.b1 + left_info.b1;

        // a2, b2 -> right_info(left_info)
        Mint a2 = right_info.a2 * left_info.a2;
        Mint b2 = right_info.a2 * left_info.b2 + right_info.b2;
        return Info(a1, b1, a2, b2);
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
    vector<int> a(n), b(n);
    SegmentTree<Info> st(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    HeavyLightDecomposition<> hld(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }

    hld.build();
    // debug(hld.rev);

    for (int i = 0; i < n; i++) {
        int u = hld.rev[i];
        st.assign(i, Info(a[u], b[u], a[u], b[u]));
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p, c, d;
            cin >> p >> c >> d;
            int timestamp = hld.in[p];
            st.assign(timestamp, Info(c, d, c, d));
        } else {
            int u, v, x;
            cin >> u >> v >> x;
            // u 在里面， v 在外面
            Info left(1, 0), right(1, 0);
            while (true) {
                if (hld.head[u] == hld.head[v]) {
                    int idx1 = hld.in[u];
                    int idx2 = hld.in[v];
                    auto it = st.rangeQuery(min(idx1, idx2), max(idx1, idx2) + 1);
                    if (idx1 < idx2) {
                        Info tmp = Info(it.a2, it.b2);
                        right = Info::merge(right, tmp, 0, 0);
                    } else {
                        Info tmp = Info(it.a1, it.b1);
                        left = Info::merge(tmp, left, 0, 0);
                    }
                    break;
                } else {
                    if (hld.in[u] > hld.in[v]) {
                        int h = hld.head[u];
                        int idx1 = hld.in[h];
                        int idx2 = hld.in[u];
                        auto it = st.rangeQuery(idx1, idx2 + 1);
                        Info tmp = Info(it.a1, it.b1);
                        left = Info::merge(tmp, left, 0, 0);
                        u = hld.par[h];
                    } else {
                        int h = hld.head[v];
                        int idx1 = hld.in[h];
                        int idx2 = hld.in[v];
                        auto it = st.rangeQuery(idx1, idx2 + 1);
                        Info tmp = Info(it.a2, it.b2);
                        right = Info::merge(right, tmp, 0, 0);
                        // debug(right.a1, right.b1, right.a2, right.b2);
                        v = hld.par[h];
                    }
                }
            }
            // debug(left.a1, left.b1);
            // debug(right.a1, right.b1);
            Info res = Info::merge(right, left, 0, 0);
            cout << res.a1 * x + res.b1 << endl;
        }
    }
    return 0;
}