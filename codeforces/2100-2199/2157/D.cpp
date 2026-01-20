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
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];

        if (a[i] < l) {
            ans += l - a[i];
            a[i] = l;
        } else if (a[i] > r) {
            ans += a[i] - r;
            a[i] = r;
        }

    }
    sort(a.begin(), a.end());


    int half = n / 2;
    for (int i = 0; i < half; i++) {
        ans += abs(a[i] - a[n - i - 1]);
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