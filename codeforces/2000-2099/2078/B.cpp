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
    int n, k;
    cin >> n >> k;

    if (k % 2 == 0) {
        for (int i = 1; i <= n; i++) {
            if (i == n - 1) {
                cout << n << ' ';
            } else {
                cout << n - 1 << ' ';
            }
        }
        cout << '\n';
    } else {
        for (int i = 1; i <= n; i++) {
            if (i == n) {
                cout << n - 1 << ' ';
            } else {
                cout << n << ' ';
            }
        }
        cout << '\n';
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