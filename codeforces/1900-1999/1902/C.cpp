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
    int n;
    cin >> n;
    vector<int> a(n);
    set<int> S;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        S.insert(a[i]);
    }
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    sort(a.begin(), a.end());

    int g = a[1] - a[0];
    for (int i = 1; i < n - 1; i++) {
        g = __gcd(g, a[i + 1] - a[i]);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (a[n - 1] - a[i]) / g;
    }
    debug(ans, g);
    int step = a[n - 1] - a[0];
    int k = step / g;
    if (k == n - 1) {
        ans += n;
    } else {
        int now = a[n - 1];
        while (S.count(now)) {
            now -= g;
            ans++;
        }
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