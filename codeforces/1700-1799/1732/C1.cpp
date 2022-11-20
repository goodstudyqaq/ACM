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
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    vector<ll> sum(n + 1);
    vector<ll> xor_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        xor_sum[i] = xor_sum[i - 1] ^ a[i];
    }
    ll mx = sum[n] - xor_sum[n];

    int L, R;
    cin >> L >> R;

    int ansL = 1, ansR = n;
    for (int i = 1; i <= n; i++) {
        ll tmp = sum[i] - xor_sum[i];
        if (tmp < mx) {
            continue;
        }

        int l = 1, r = i;
        int res = 1;
        while (l <= r) {
            int m = l + r >> 1;
            ll tmp2 = (sum[i] - sum[m - 1]) - (xor_sum[i] ^ xor_sum[m - 1]);
            if (tmp2 == mx) {
                res = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        if (ansR - ansL + 1 > i - res + 1) {
            ansL = res;
            ansR = i;
        }
    }
    cout << ansL << ' ' << ansR << endl;
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
}