#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<long long> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    vector<int> next(n + 2, n + 1), last(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (a[i] != a[i - 1]) {
            last[i] = i - 1;
        } else {
            last[i] = last[i - 1];
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] != a[i + 1]) {
            next[i] = i + 1;
        } else {
            next[i] = next[i + 1];
        }
    }

    auto get_left_idx = [&](int idx) {
        int val = a[idx];
        int l = 1, r = idx - 1;
        int ans = 0;
        while (l <= r) {
            int m = l + r >> 1;
            long long tmp = sum[idx] - sum[m - 1];
            if (tmp > 2LL * val) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return ans;
    };

    auto get_right_idx = [&](int idx) {
        int val = a[idx];
        int l = idx + 1, r = n;
        int ans = n + 1;
        while (l <= r) {
            int m = l + r >> 1;
            long long tmp = sum[m] - sum[idx - 1];
            if (tmp > 2LL * val) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    };

    for (int i = 1; i <= n; i++) {
        // 左边
        int val = a[i];
        if (a[i - 1] > val || (i + 1 <= n && a[i + 1] > val)) {
            cout << 1 << ' ';
            continue;
        }



        int left_idx = get_left_idx(i);
        left_idx = min(left_idx, last[i - 1]);
        int left_len = (left_idx == 0 ? 1e9 : i - left_idx);

        int right_idx = get_right_idx(i);
        right_idx = max(right_idx, next[i + 1]);
        int right_len = (right_idx == n + 1 ? 1e9 : right_idx - i);

        int ans = min(left_len, right_len);
        // debug(i, left_idx, right_idx);

        if (ans == 1e9) {
            ans = -1;
        }
        cout << ans << ' ';
    }
    cout << endl;
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