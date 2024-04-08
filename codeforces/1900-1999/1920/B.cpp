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
    int n, k, x;

    cin >> n >> k >> x;
    vector<int> a(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a.begin() + 1, a.begin() + 1 + n);

    int ans = -1e9;
    int l = n;
    int lsum = 0;
    for (int i = n; i >= n - k && i >= 0 && a[i] >= 0; i--) {
        while (i - l < x && a[l] > 0) {
            lsum += a[l];
            l--;
        }
        ans = max(ans, sum - lsum * 2);
        sum -= a[i];
        lsum -= a[i];
    }
    cout << ans << endl;
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