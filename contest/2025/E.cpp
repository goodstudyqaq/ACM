#include <bits/stdc++.h>

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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<long long> l(n), r(n);
    long long mi = 0, mx = 0;
    typedef pair<long long, long long> pll;
    vector<pll> range(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        mi += l[i];
        mx += r[i];
        range[i] = {mi, mx};
    }
    // [mi, mx]
    if (mx < 0 || mi > 0) {
        cout << "No\n";
        return 0;
    }

    vector<long long> ans(n);
    long long right_sum = 0;

    auto get_internal_left = [&](long long l1, long long r1, long long l2, long long r2) -> pair<long long, bool> {
        if (r1 < l2) return {-1, false};
        if (r2 < l1) return {-1, false};

        if (l1 < l2) {
            return {l2, true};
        } else {
            return {l1, true};
        }
    };

    for (int i = n - 1; i >= 0; i--) {
        if (i == 0) {
            ans[i] = -right_sum;
        } else {
            long long left_mi = range[i - 1].first, left_mx = range[i - 1].second;

            long long now_l = l[i], now_r = r[i];
            now_l += right_sum, now_r += right_sum;

            // [-left_mx, -left_mi] 和 [now_l, now_r] 求交集
            auto choose = get_internal_left(-left_mx, -left_mi, now_l, now_r);
            if (!choose.second) {
                cout << "No\n";
                return 0;
            }
            ans[i] = choose.first - right_sum;
            right_sum = choose.first;
        }
    }
    cout << "Yes\n";
    for (auto it : ans) {
        cout << it << ' ';
    }
    cout << '\n';
}