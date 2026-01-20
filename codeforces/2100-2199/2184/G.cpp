#include <bits/stdc++.h>

#include "structure/segment-tree/segment-tree.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

struct Info {
    // 默认值
    int mi = 1e9;
    int l, r;
    Info(int mi = 1e9, int l = -1, int r = -1) : mi(mi), l(l), r(r) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info(min(left_info.mi, right_info.mi), l, r);
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
        infos[i].mi = a[i];
        infos[i].l = infos[i].r = i;
    }
    debug(a);

    SegmentTree<Info> seg(infos);

    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int i, x;
            cin >> i >> x;
            i--;
            seg.assign(i, Info{x, i, i});
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            auto f = [&](const Info& info) -> bool {
                return info.mi <= info.r - l;
            };

            auto idx = seg.find_first(l, r, f);
            debug(l, r, idx);
            if (idx == -1) {
                cout << 0 << '\n';
            } else {
                auto it = seg.rangeQuery(l, idx + 1);
                debug(it.mi, idx);
                if (it.mi == idx - l) {
                    cout << 1 << '\n';
                } else {
                    cout << 0 << '\n';
                }
            }
        }
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