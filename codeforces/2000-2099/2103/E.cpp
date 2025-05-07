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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    set<int> S;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        S.insert(a[i]);
    }
    bool ok = false;
    for (auto it : S) {
        if (S.count(k - it)) {
            ok = true;
            break;
        }
    }
    if (!ok) {
        cout << -1 << '\n';
        return;
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
    return 0;
}