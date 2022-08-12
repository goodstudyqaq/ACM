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
    vector<int> a(n);
    int mx = 0;
    int mx_idx = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (mx < a[i]) {
            mx = a[i];
            mx_idx = i;
        }
    }

    auto check = [&](int idx) {
        for (int i = idx - 1; i >= 0; i--) {
            if (a[i] <= a[i + 1]) continue;
            return false;
        }

        for (int i = idx + 1; i < n; i++) {
            if (a[i] <= a[i - 1]) continue;
            return false;
        }

        return true;
    };

    if (check(mx_idx)) {
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
}