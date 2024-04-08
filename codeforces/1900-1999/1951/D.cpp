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
    long long n, k;
    cin >> n >> k;
    if (k > n) {
        cout << "NO" << endl;
        return;
    }
    if (k == n / 2) {
        cout << "YES" << endl;
        cout << 1 << endl;
        cout << 2 << endl;
        return;
    }

    if (k < n / 2) {
        cout << "YES" << endl;
        long long tmp = n - k + 1;
        cout << 2 << endl;
        cout << tmp << ' ' << 1 << endl;
        return;
    }

    // k > n / 2
    if (k == n) {
        cout << "YES" << endl;
        cout << 1 << endl;
        cout << 1 << endl;
        return;
    }
    if (n % 2 && k == n / 2 + 1) {
        cout << "YES" << endl;
        cout << 2 << endl;
        cout << 2 << ' ' << 1 << endl;
        return;
    }
    cout << "NO" << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    for (int i = 1; i <= 100; i++) {
        debug(i, 100 / i, 100 % i);
    }

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}