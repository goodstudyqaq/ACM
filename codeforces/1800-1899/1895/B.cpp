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
    cin >> n;
    vector<int> a(n * 2);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        x[i] = a[i];
        y[i] = a[i + n];
    }

    cout << x[n - 1] - x[0] + y[n - 1] - y[0] << endl;
    for (int i = 0; i < n; i++) {
        cout << x[i] << ' ' << y[i] << endl;
    }
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