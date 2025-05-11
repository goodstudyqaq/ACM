#include <bits/stdc++.h>

#include <functional>
#include <queue>

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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans += a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    const int BIT = 1 << m;
    vector<int> val(BIT);
    for (int i = 0; i < BIT; i++) {
        int now = (1 << 30) - 1;
        for (int j = 0; j < m; j++) {
            if ((i >> j) & 1) {
                now &= b[j];
            }
        }
        val[i] = now;
    }

    vector<int> diff;
    for (int i = 0; i < n; i++) {
        vector<int> mi(m + 1, 1 << 30);
        mi[0] = a[i];
        for (int j = 0; j < BIT; j++) {
            int one = __builtin_popcount(j);
            mi[one] = min(mi[one], a[i] & val[j]);
        }
        for (int j = 0; j < m; j++) {
            int tmp = mi[j] - mi[j + 1];
            diff.push_back(tmp);
        }
    }
    sort(diff.begin(), diff.end(), greater<>());
    debug(diff);
    debug(ans);

    for (int i = 0; i < k; i++) {
        ans -= diff[i];
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