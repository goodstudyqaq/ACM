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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> V;
    for (int i = 1; i <= n; i++) {
        if (a[i] > a[k]) {
            V.push_back(i);
        }
    }

    if (V.size() == 0) {
        cout << n - 1 << endl;
        return;
    }

    if (V.size() == 1) {
        if (V[0] > k) {
            cout << V[0] - 2 << endl;
        } else {
            int ans = max(V[0] - 2, k - V[0] - 1 + (V[0] == 1 ? 0 : 1));
            cout << ans << endl;
        }
        return;
    }
    vector<int> V2;
    for (int i = 1; i < k; i++) {
        if (a[i] > a[k]) {
            V2.push_back(i);
        }
    }

    if (V2.size() == 0) {
        cout << V[0] - 2 << endl;
        return;
    }
    if (V2.size() == 1) {
        int ans = max(V[0] - 2, k - V[0] - 1 + (V[0] == 1 ? 0 : 1));
        cout << ans << endl;
        return;
    } else {
        int ans = max(V[0] - 2, V[1] - V[0] - 1 + (V[0] == 1 ? 0 : 1));
        cout << ans << endl;
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