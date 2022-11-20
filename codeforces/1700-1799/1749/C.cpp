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
    int one = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    auto check = [&](int k) {
        // k 个 1 + 2, 3, 4, ... k
        int m = 2 * k - 1;
        if (n < m) return false;
        for (int i = 0; i < m; i++) {
            int x = (i < k) ? 1 : i - k + 2;
            if (a[i] > x) return false;
        }
        return true;
    };

    for (int k = 100; k >= 1; k--) {
        if (check(k)) {
            cout << k << endl;
            return;
        }
    }
    cout << 0 << endl;
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