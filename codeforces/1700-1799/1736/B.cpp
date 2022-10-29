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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> b(n + 2);
    b[1] = a[1];
    b[n + 1] = a[n];

    for (int i = 2; i <= n; i++) {
        int tmp1 = a[i - 1];
        int tmp2 = a[i];
        b[i] = 1LL * tmp1 * tmp2 / __gcd(tmp1, tmp2);
    }

    for (int i = 1; i <= n; i++) {
        if (__gcd(b[i], b[i + 1]) != a[i]) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
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