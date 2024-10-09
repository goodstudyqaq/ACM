#include <bits/stdc++.h>

#include <algorithm>

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
    int add;
    Tag(int add = 0) : add(add) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.add) {
            add += v.add;
        }
    }
};

struct Info {
    // 默认值
    int mi, cnt;
    Info(int mi = 0, int cnt = 0) : mi(mi), cnt(cnt) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.add) {
            mi += v.add;
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        int mi = min(left_info.mi, right_info.mi);
        int cnt = 0;
        if (mi == left_info.mi) {
            cnt += left_info.cnt;
        }
        if (mi == right_info.mi) {
            cnt += right_info.cnt;
        }
        return {mi, cnt};
    }
};
// {x1, 1/-1, y1, y2}
typedef array<int, 4> event;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<event> events;
    vector<int> vy;
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        vy.push_back(y1);
        vy.push_back(y2);
        events.push_back({x1, 1, y1, y2});
        events.push_back({x2, -1, y1, y2});
    }
    sort(events.begin(), events.end());
    sort(vy.begin(), vy.end());
    vy.erase(unique(vy.begin(), vy.end()), vy.end());
    long long ans = 0;
    vector<Info> inits(vy.size());
    for (int i = 0; i < vy.size() - 1; i++) {
        inits[i] = {0, vy[i + 1] - vy[i]};
    }
    LazySegmentTree<Info, Tag> seg(inits);

    int lastx = 0;
    long long total = vy.back() - vy[0];
    for (auto &e : events) {
        auto tmp = seg.rangeQuery(0, vy.size());
        if (tmp.mi != 0) {
            ans += (e[0] - lastx) * total;
        } else {
            ans += (e[0] - lastx) * (total - tmp.cnt);
        }
        lastx = e[0];
        debug(e, tmp.mi, tmp.cnt, ans);
        int y1 = e[2], y2 = e[3];
        int idx1 = lower_bound(vy.begin(), vy.end(), y1) - vy.begin();
        int idx2 = lower_bound(vy.begin(), vy.end(), y2) - vy.begin();
        seg.rangeUpdate(idx1, idx2, Tag(e[1]));
    }
    cout << ans << endl;
}