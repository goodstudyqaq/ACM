#include <bits/stdc++.h>

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

void solve() {
    int n, k;
    cin >> n >> k;
    // 选一个长度至少为 k 的子数组，让中位数最大
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int l = 1, r = n;
    int ans = -1;

    vector<int> sumb(n + 1);

    auto check = [&](int val) -> pii {
        for (int i = 0; i < n; i++) {
            int b = (a[i] >= val ? 1 : -1);
            sumb[i + 1] = b;
            sumb[i + 1] += sumb[i];
        }
        int mi = 0;
        int l = 0;

        for (int i = k; i <= n; i++) {
            int val = sumb[i];
            if (val >= mi) {
                return {l + 1, i};
            }
            if (sumb[i - k + 1] < mi) {
                mi = sumb[i - k + 1];
                l = i - k + 1;
            }
        }
        return {-1, -1};
    };

    int ansl = -1, ansr = -1;
    while (l <= r) {
        int m = l + r >> 1;
        auto tmp = check(m);
        if (tmp.first != -1) {
            ans = m;
            ansl = tmp.first;
            ansr = tmp.second;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    cout << ans << ' ' << ansl << ' ' << ansr << '\n';
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