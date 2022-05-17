#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<ll> sum(n + 1), cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        cnt[i] = cnt[i - 1] + (a[i] == 0);
    }

    if (sum[n] - cnt[n] * k > 0 || sum[n] + cnt[n] * k < 0) {
        cout << -1 << endl;
        return 0;
    }

    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ll the_sum = sum[j] - sum[i - 1];
            ll the_cnt = cnt[j] - cnt[i - 1];

            ll other_sum = sum[n] - the_sum;
            ll other_cnt = cnt[n] - the_cnt;

            ll L = max(the_sum - the_cnt * k, -(other_sum + other_cnt * k));
            ll R = min(the_sum + the_cnt * k, -(other_sum - other_cnt * k));
            ans = max(ans, abs(L) + 1);
            ans = max(ans, abs(R) + 1);
        }
    }
    cout << ans << endl;
    return 0;
}