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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n - 1; i++) {
        if (a[i] == -1) a[i] = 0;
    }
    if (a[0] == -1 && a[n - 1] == -1) {
        a[0] = a[n - 1] = 0;
    } else if (a[0] == -1) {
        a[0] = a[n - 1];
    } else if (a[n - 1] == -1) {
        a[n - 1] = a[0];
    }
    cout << abs(a[n - 1] - a[0]) << '\n';
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
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