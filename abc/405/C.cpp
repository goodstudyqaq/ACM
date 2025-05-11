#include <bits/stdc++.h>

#include <limits>

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
    vector<long long> a(n), sum(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum[i] = a[i];
        if (i) {
            sum[i] += sum[i - 1];
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i] * (sum[n - 1] - sum[i]);
    }
    cout << ans << '\n';
    return 0;
}