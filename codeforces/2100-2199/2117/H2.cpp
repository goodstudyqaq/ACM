/*
MLE....
*/
#include <bits/stdc++.h>

#include "./structure/segment-tree/dynamic-segment-tree.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

struct Info {
    // 默认值
    int lsum, rsum, mx_sum, sum;

    Info(int lsum, int rsum, int mx_sum, int sum) : lsum(lsum), rsum(rsum), mx_sum(mx_sum), sum(sum) {}
    Info(int len = 1) {
        lsum = 0, rsum = 0, mx_sum = 0, sum = -len;
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int lsum = max(left_info.lsum, left_info.sum + right_info.lsum);
        int rsum = max(right_info.rsum, right_info.sum + left_info.rsum);
        int mx_sum = max({0, left_info.mx_sum, right_info.mx_sum, left_info.rsum + right_info.lsum});
        lsum = max(0, lsum);
        rsum = max(0, rsum);
        int sum = left_info.sum + right_info.sum;
        return Info(lsum, rsum, mx_sum, sum);
    }

    string to_string() {
        return "";
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<DynamicSegtree<Info>> seg(n + 1, DynamicSegtree<Info>(n));
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        seg[a[i]].assign(i, Info(1, 1, 1, 1));
    }

    multiset<int> S;
    for (int i = 1; i <= n; i++) {
        S.insert(seg[i].rangeQuery(0, n).mx_sum);
    }
    debug(S);

    while (q--) {
        int idx, val;
        cin >> idx >> val;
        idx--;
        S.extract(seg[a[idx]].rangeQuery(0, n).mx_sum);
        seg[a[idx]].del(idx);
        S.insert(seg[a[idx]].rangeQuery(0, n).mx_sum);

        S.extract(seg[val].rangeQuery(0, n).mx_sum);
        seg[val].assign(idx, Info(1, 1, 1, 1));
        S.insert(seg[val].rangeQuery(0, n).mx_sum);

        a[idx] = val;

        cout << *S.rbegin() / 2 << ' ';
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