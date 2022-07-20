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
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    int mi_time = 0;
    // int l = 1, r = 1e9;
    int l = 1, r = 1e9;
    debug(l, r);

    auto check = [&](int t) -> bool {
        int j = 1;
        ll val = 0;
        ll the_sum = 0;
        for (int i = 1; i <= n; i++) {
            val += t;
            while (j <= n && the_sum + a[j] <= val) {
                the_sum += a[j];
                j++;
            }
            if (j == n + 1) return true;
            if (j == i) return false;
        }
        return true;
    };

    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            mi_time = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    debug(mi_time);

    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t < mi_time) {
            cout << -1 << endl;
        } else {
            ll ans = (sum - 1) / t + 1;
            cout << ans << endl;
        }
    }
}