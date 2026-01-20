#include <bits/stdc++.h>

#include "structure/segment-tree/lazy-segment-tree.hpp"

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

struct Tag {
    // 默认值
    int val;
    Tag(int val = -1) : val(val) {
    }
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag& v, int l, int r) {
        if (v.val != -1) {
            val = v.val;
        }
    }
};

struct Info {
    // 默认值
    ll sum;
    ll mx;
    Info(ll sum = 0, ll mx = 0) : sum(sum), mx(mx) {
    }

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag& v, int l, int r) {
        if (v.val != -1) {
            sum = 0;
            mx = 0;
        }
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        ll sum = left_info.sum + right_info.sum;
        ll mx = max(left_info.mx, right_info.mx);
        return Info(sum, mx);
    }
};

struct Tag2 {
    // 默认值
    int mi;
    Tag2(int mi = 1e9) : mi(mi) {
    }
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag2& v, int l, int r) {
        if (v.mi != 1e9) {
            mi = min(mi, v.mi);
        }
    }
};
struct Info2 {
    // 默认值
    int mi;
    Info2(int mi = 1e9) : mi(mi) {
    }

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag2& v, int l, int r) {
        if (v.mi != 1e9) {
            mi = min(mi, v.mi);
        }
    }
    static Info2 merge(const Info2& left_info, const Info2& right_info, int l, int r) {
        int mi = min(left_info.mi, right_info.mi);
        return Info2(mi);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), c(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    vector<int> L(n, -1), R(n, n);
    vector<int> stk;

    for (int i = 0; i < n; i++) {
        while (stk.size() && a[stk.back()] <= a[i]) {
            stk.pop_back();
        }
        if (stk.size()) {
            L[i] = stk.back();
        }
        stk.push_back(i);
    }

    stk.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (stk.size() && a[stk.back()] <= a[i]) {
            stk.pop_back();
        }
        if (stk.size()) {
            R[i] = stk.back();
        }
        stk.push_back(i);
    }

    const int inf = 1e9;
    LazySegmentTree<Info2, Tag2> seg2(n);


    for (int i = 0; i < n; i++) {
        int l = L[i], r = R[i];
        l++;
        seg2.rangeUpdate(l, r, Tag2(c[i]));
    }

    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
        int val = seg2.rangeQuery(i, i + 1).mi;
        infos[i] = Info(val, val);
    }
    LazySegmentTree<Info, Tag> seg(infos);

    auto get_ans = [&]() {
        auto it = seg.rangeQuery(0, n);
        return it.sum - it.mx;
    };
    cout << get_ans() << ' ';

    for (int i = 0; i < n; i++) {
        int idx = p[i];

        int l = L[idx], r = R[idx];
        l++, r--;
        seg.rangeUpdate(l, r + 1, Tag(0));
        cout << get_ans() << ' ';
    }
    cout << '\n';
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