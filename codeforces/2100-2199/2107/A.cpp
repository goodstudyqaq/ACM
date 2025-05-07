#include <bits/stdc++.h>

#include <algorithm>

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

    bool eq = true;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[0]) {
            eq = false;
            break;
        }
    }
    if (eq) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";

    int mx = *max_element(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        if (a[i] == mx) {
            cout << 1 << ' ';
        } else {
            cout << 2 << ' ';
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