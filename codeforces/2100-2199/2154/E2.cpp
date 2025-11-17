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
    vector<long long> a(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.begin() + n + 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    auto get_res = [&](int idx) -> long long {
        int len = min(idx - 1, n - idx);
        long long res = sum[n];
        for (int j = 1; j <= len; j++) {
            int len2 = j * k;
            if (len2 >= idx - 1) {
                len2 = idx - 1;
            }
            long long tmp = sum[n] + a[idx] * len2 - sum[len2] - (sum[idx + j] - sum[idx] - a[idx] * j);
            if (idx == 5) {
                debug(tmp, j, len2, len);
            }
            res = max(res, tmp);
            if (len2 == idx - 1) {
                break;
            }
        }
        return res;
    };

    long long ans = sum[n];
    for (int i = 1; i <= n; i++) {
        long long tmp = get_res(i);
        ans = max(ans, tmp);
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