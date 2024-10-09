#include <bits/stdc++.h>

#include <algorithm>

#include "./structure/others/binary-indexed-tree.hpp"

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
typedef array<int, 4> event;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<event> events;
    vector<int> vx;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        events.push_back({y, 0, x});
        vx.push_back(x);
    }
    sort(vx.begin(), vx.end());
    vx.erase(unique(vx.begin(), vx.end()), vx.end());
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        events.push_back({y2, 1, x2, i});
        events.push_back({y1 - 1, 1, x1 - 1, i});
        events.push_back({y2, 2, x1 - 1, i});
        events.push_back({y1 - 1, 2, x2, i});
    }
    sort(events.begin(), events.end());
    BIT<int> bit(vx.size());

    for (int i = 0; i < events.size(); i++) {
        if (events[i][1] == 0) {
            int idx = lower_bound(vx.begin(), vx.end(), events[i][2]) - vx.begin() + 1;
            bit.add(idx, 1);
        } else {
            int idx = upper_bound(vx.begin(), vx.end(), events[i][2]) - vx.begin();
            int tmp = idx == 0 ? 0 : bit.query(idx);
            if (events[i][1] == 1) {
                ans[events[i][3]] += tmp;
            } else {
                ans[events[i][3]] -= tmp;
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}