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

    if (n <= 5) {
        vector<int> res = {1, 2, 2, 3, 3};
        cout << res[n - 1] << endl;
        for (int i = 0; i < n; i++) {
            cout << res[i] << ' ';
        }
        cout << endl;
        return;
    }

    cout << 4 << endl;
    for (int i = 1; i <= n; i++) {
        cout << (i % 4) + 1 << ' ';
    }
    cout << endl;
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