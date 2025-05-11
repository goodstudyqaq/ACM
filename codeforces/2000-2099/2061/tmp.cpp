#line 1 "E.cpp"
#include <bits/stdc++.h>

#line 4 "E.cpp"

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
    priority_queue<int> Q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        Q.push(a[i]);
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    while (k--) {
        auto it = Q.top();
        Q.pop();

        int mi = it;
        for (int i = 0; i < m; i++) {
            mi = min(mi, it & b[i]);
        }
        Q.push(mi);
    }

    long long ans = 0;
    while (!Q.empty()) {
        ans += Q.top();
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
