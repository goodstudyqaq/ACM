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
    vector<int> V;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i != 0 && i != n - 1) {
            V.push_back(a[i]);
        }
    }
    sort(V.begin(), V.end());

    int now = a[0];
    int end = a[n - 1];

    int idx = 0;
    int ans = 2;
    while (end > 2 * now) {
        debug(end, now);
        if (idx == V.size()) {
            cout << -1 << '\n';
            return;
        }
        int go = idx;
        while (go < V.size() && V[go] <= 2 * now) {
            go++;
        }
        go--;
        if (go < idx) {
            cout << -1 << '\n';
            return;
        }

        ans++;
        now = V[go];
        idx = go + 1;
    }
    cout << ans << '\n';
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