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
    long long k;
    cin >> n >> k;
    vector<long long> a(n * 2 + 1), b(n * 2 + 1);
    long long suma = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        suma += a[i];
        a[n + i] = a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        b[n + i] = b[i];
    }
    // debug(a, b);
    if (suma == k) {
        cout << 0 << '\n';
        return;
    }

    vector<long long> sum(n * 2 + 1);
    for (int i = 1; i <= n * 2; i++) {
        sum[i] = a[i] - b[i] + sum[i - 1];
    }
    int pos = n;
    for (int i = n; i <= n * 2; i++) {
        if (sum[i] < sum[pos]) {
            pos = i;
        }
    }
    // debug(sum, pos);
    int l = 1, r = n;
    int ans = 1;

    vector<int> stk(n + 2);
    auto check = [&](int x) -> bool {
        int l = 1, r = 0;
        long long need = 0;

        for (int i = pos; i >= pos - n; i--) {
            while (l <= r && stk[l] - i > x) {
                l++;
            }

            if (pos - i >= x) {
                need += max(0LL, sum[stk[l]] - sum[i]);
            }

            while (l <= r && sum[stk[r]] >= sum[i]) {
                r--;
            }
            stk[++r] = i;
        }
        return need <= k;
    };

    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
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