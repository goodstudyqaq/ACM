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
    int n;
    cin >> n;
    vector<int> a(n);

    const int m = 100;
    vector<vector<int>> idx(m + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        idx[a[i]].push_back(i);
    }

    int ans = -1;
    vector<int> sum(n + 1);

    auto check = [&](int val, int mi) {
        for (int i = 0; i < n; i++) {
            if (a[i] < val) {
                sum[i + 1] = -1;
            } else {
                sum[i + 1] = 1;
            }
            if (i) {
                sum[i + 1] += sum[i];
            }
        }
        int mi_sum = 1e9;
        int l = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i - 1] == mi) {
                while (l < i) {
                    mi_sum = min(mi_sum, sum[l]);
                    l++;
                }
            }
            int val = sum[i];
            if (val - mi_sum >= 0) {
                return true;
            }
        }
        return false;
    };

    for (int mi = 1; mi <= m; mi++) {
        if (idx[mi].size() == 0) continue;
        int l = mi, r = m;
        int tmp = mi;
        while (l <= r) {
            int mid = l + r >> 1;
            if (check(mid, mi)) {
                tmp = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        debug(mi, tmp);
        ans = max(ans, tmp - mi);
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