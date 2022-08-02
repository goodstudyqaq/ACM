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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.begin() + 1 + n);

    vector<ll> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    while (q--) {
        ll x;
        cin >> x;
        int idx = lower_bound(a.begin() + 1, a.begin() + 1 + n, x) - a.begin();
        // [idx, n] >= x
        ll num = n - idx + 1;
        ll ans = sum[n] - sum[idx - 1] - num * x;
        ll num2 = n - num;
        ans += num2 * x - sum[idx - 1];
        cout << ans << endl;
    }
    return 0;
}