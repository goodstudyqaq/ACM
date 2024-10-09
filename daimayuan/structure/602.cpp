#include <bits/stdc++.h>

#include <limits>

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

const int inf = numeric_limits<int>::max();
struct Info {
    // 默认值
    int mi;
    Info(int mi = inf) : mi(mi) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info(min(left_info.mi, right_info.mi));
    }
    string to_string() {
        return "";
    }
};

// {x, 0/1, i}
typedef array<int, 3> event;
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    vector<event> events;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        events.push_back({a[i], 0, i});
    }

    vector<array<int, 3>> que(q);
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        que[i] = {l, r, x};
        events.push_back({x, 1, i});
    }

    sort(events.begin(), events.end(), [&](event& a, event& b) {
        if (a[0] != b[0]) return a[0] > b[0];
        return a[1] < b[1];
    });

    SegmentTree<Info> seg(n + 1);

    vector<int> ans(q);
    for (auto& e : events) {
        if (e[1] == 0) {
            seg.assign(e[2], Info(e[0]));
        } else {
            int tmp = seg.rangeQuery(que[e[2]][0], que[e[2]][1] + 1).mi;
            if (tmp == inf) tmp = -1;
            ans[e[2]] = tmp;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}