#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    ll n;
    cin >> n;

    if (n % 2) {
        cout << -1 << endl;
        return;
    }
    if (n <= 2) {
        cout << -1 << endl;
        return;
    }

    ll left = n / 4;
    ll right = n / 6;
    if (n % 6) {
        right++;
    }
    cout << right << ' ' << left << endl;
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