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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    if (a[n - 1] != b[n - 1]) {
        cout << "NO\n";
        return;
    }

    for (int i = n - 2; i >= 0; i--) {
        if (a[i] == b[i]) {
            continue;
        }

        if ((a[i] ^ a[i + 1]) == b[i]) {
            continue;
        }
        if ((a[i] ^ b[i + 1]) == b[i]) {
            continue;
        }

        cout << "NO\n";
        return;
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