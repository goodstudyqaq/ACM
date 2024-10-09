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
    int mi;
    Info(int mi = 0) : mi(mi) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info(min(left_info.mi, right_info.mi));
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
    vector<int> a(n + 1);
    vector<int> pos(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = min(a[i], n + 1);
    }
    SegmentTree<Info> seg(n + 2);
    vector<vector<pair<int, int>>> que(n + 1);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        que[r].push_back({l, i});
    }

    vector<int> ans(q);
    for (int i = 1; i <= n; i++) {
        seg.assign(a[i], Info(i));
        for (auto& it : que[i]) {
            int l = it.first, idx = it.second;

            auto f = [&](const Info& info) {
                return info.mi < l;
            };
            int tmp = seg.find_first(0, n + 2, f);
            ans[idx] = tmp;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}