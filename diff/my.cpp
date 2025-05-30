#include <bits/stdc++.h>

#include <queue>

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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    priority_queue<pii> Q;
    for (int i = 0; i < n; i++) {
        int mx = 0;
        for (int j = 0; j < m; j++) {
            int v = a[i] & b[j];
            mx = max(mx, a[i] - v);
        }
        Q.push({mx, a[i]});
    }

    while (k--) {
        auto it = Q.top();
        Q.pop();

        int now = it.second - it.first;

        int mx = 0;
        for (int j = 0; j < m; j++) {
            int v = now & b[j];
            mx = max(mx, now - v);
        }
        Q.push({mx, now});
    }

    long long ans = 0;
    while (!Q.empty()) {
        ans += Q.top().second;
        Q.pop();
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