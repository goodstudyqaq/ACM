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
    vector<int> even;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 2 == 0) {
            even.push_back(i);
        }
    }
    if (even.size() >= 2) {
        cout << a[even[0]] << ' ' << a[even[1]] << '\n';
        return;
    }

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) continue;
        for (int j = i + 1; j < n; j++) {
            int tmp = a[j] % a[i];
            if (tmp % 2 == 0) {
                cout << a[i] << ' ' << a[j] << '\n';
                return;
            }
        }
    }
    cout << -1 << '\n';
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