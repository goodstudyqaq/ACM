#include <bits/stdc++.h>

#include <algorithm>
#include <climits>
#include <limits>

#include "./structure/segment-tree/segment-tree.hpp"

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
    int mi;
    Info(int mi = 1e9) : mi(mi) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info(min(left_info.mi, right_info.mi));
    }
    string to_string() {
        return "";
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(2 * n), b(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[n + i] = a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[n + i] = b[i];
    }

    vector<long long> sum(2 * n);
    vector<long long> X;
    X.push_back(0);
    for (int i = 0; i < 2 * n; i++) {
        sum[i] = a[i] - b[i];
        if (i) {
            sum[i] += sum[i - 1];
        }
        X.push_back(sum[i]);
    }
    sort(X.begin(), X.end());
    X.resize(unique(X.begin(), X.end()) - X.begin());

    int sz = X.size();
    SegmentTree<Info> seg(sz);

    int ans = 1;
    for (int i = 2 * n - 1; i >= 0; i--) {
        if (i < n) {
            long long val = a[i] - b[i];
            if (val > 0) {
                long long tmp = i == 0 ? 0 : sum[i - 1];
                int idx = upper_bound(X.begin(), X.end(), tmp) - X.begin();
                auto it = seg.rangeQuery(0, idx).mi;
                // debug(i, it);
                if (it != 1e9) {
                    ans = max(ans, it - i + 1);
                }
            }

        }
        long long val = sum[i];
        int idx = lower_bound(X.begin(), X.end(), val) - X.begin();
        seg.update(idx, Info(i));
    }
    cout << ans << '\n';
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