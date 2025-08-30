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
    vector<long long> a(n);
    long long g = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        g = gcd(g, a[i]);
    }

    if (g > 1) {
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
        return;
    }

    if (k % 2) {
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == 0) {
                cout << a[i] << ' ';
            } else {
                cout << a[i] + k << ' ';
            }
        }
        cout << '\n';
        return;
    }
    long long chose = k + 1;

    for (int i = 0; i < n; i++) {
        if (a[i] % chose == 0) {
            cout << a[i] << ' ';
        } else {
            int v1 = a[i] % chose;
            cout << a[i] + (k * v1) << ' ';
        }
    }
    cout << '\n';
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