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
    bool reverse;
    Tag(bool reverse = false) : reverse(reverse) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.reverse) {
            reverse ^= v.reverse;
        }
    }
};

struct Info {
    // 默认值
    int cnt[2];
    Info(int _cnt[2]) {
        cnt[0] = _cnt[0];
        cnt[1] = _cnt[1];
    }
    Info() {
        cnt[0] = cnt[1] = 0;
    }

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.reverse) {
            swap(cnt[0], cnt[1]);
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        int cnt[2] = {left_info.cnt[0] + right_info.cnt[0], left_info.cnt[1] + right_info.cnt[1]};
        return Info(cnt);
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<array<int, 4>> query(m);
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            query[i] = {t, l, r, 0};
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            query[i] = {t, l, r, x};
        }
    }

    vector<long long> ans(m);
    LazySegmentTree<Info, Tag> seg(n);
    vector<Info> infos(n);
    int cnt[2];
    for (int b = 0; b < 20; b++) {
        for (int i = 0; i < n; i++) {
            int v = (a[i] >> b) & 1;
            cnt[0] = cnt[1] = 0;
            cnt[v] = 1;
            infos[i] = Info(cnt);
        }
        seg.initSegmentTree(infos);
        for (int i = 0; i < m; i++) {
            auto &q = query[i];
            if (q[0] == 1) {
                int l = q[1], r = q[2];
                auto it = seg.rangeQuery(l, r + 1);
                ans[i] += (1LL << b) * it.cnt[1];
            } else {
                int l = q[1], r = q[2], x = q[3];
                x = (x >> b) & 1;
                if (x) {
                    seg.rangeUpdate(l, r + 1, Tag(true));
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (query[i][0] == 1) {
            cout << ans[i] << '\n';
        }
    }
}
