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
    long long n, m, k;
    cin >> n >> m >> k;
    k--;

    if (m > n * (n - 1) / 2 || m < n - 1) {
        cout << "NO" << endl;
        return;
    }
    int d = 2;
    if (n == 1) {
        d = 0;
    } else if (m == n * (n - 1) / 2) {
        d = 1;
    }
    if (d < k) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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