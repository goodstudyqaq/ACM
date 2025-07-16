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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long up = 1LL * a[1] * n - a[n];
    long long down = 1LL * n * n - 1;
    if (up < 0 || up % down) {
        cout << "NO\n";
        return;
    }
    long long y = up / down;

    long long x = a[1] - 1LL * n * y;
    if (x < 0) {
        cout << "NO\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        long long val = x * i + y * (n - i + 1);
        if (val != a[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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