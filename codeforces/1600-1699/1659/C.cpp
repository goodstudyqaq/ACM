#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    int T;
    cin >> T;
    while (T--) {
        long long n, a, b;
        cin >> n >> a >> b;
        vector<long long> x(n + 1);
        vector<long long> sum(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> x[i];
            sum[i] = x[i] + sum[i - 1];
        }
        long long now = 0;

        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += b * (x[i] - now);
            debug(ans, now);
            long long tmp1 = 1LL * b * (sum[n] - 1LL * (n - i) * x[i]) + 1LL * a * (x[i] - now);
            long long tmp2 = 1LL * b * (sum[n] - 1LL * (n - i) * now);
            if (tmp1 < tmp2) {
                ans += a * (x[i] - now);
                now = x[i];
            }
        }
        cout << ans << endl;
    }
    return 0;
}