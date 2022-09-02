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
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll x;
    cin >> x;
    int ans = n;
    for (int i = 1; i <= n; i++) a[i] -= x;
    ll inf = numeric_limits<ll>::max() / 2;
    for (int i = 2; i <= n; i++) {
        if (a[i] + a[i - 1] < 0 || a[i] + a[i - 1] + a[i - 2] < 0) {
            ans--;
            a[i] = inf;
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
}