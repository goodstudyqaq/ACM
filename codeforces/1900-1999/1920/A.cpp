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
    int mx = 1e9 + 1;
    int mi = 0;
    set<int> S;
    for (int i = 1; i <= n; i++) {
        int a, x;
        cin >> a >> x;
        if (a == 1) {
            mi = max(mi, x);
        } else if (a == 2) {
            mx = min(mx, x);
        } else {
            S.insert(x);
        }
    }

    int all = max(mx - mi + 1, 0);
    for (auto it : S) {
        if (it >= mi && it <= mx) {
            all--;
        }
    }
    cout << all << endl;
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