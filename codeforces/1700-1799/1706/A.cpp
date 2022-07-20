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
    int n, m;
    cin >> n >> m;

    string ans(m + 1, 'B');
    vector<int> a(n + 1);
    vector<int> vis(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int x = a[i], y = m + 1 - a[i];
        if (x > y) swap(x, y);

        if (vis[x] == 0) {
            ans[x] = 'A';
            vis[x] = 1;
        } else {
            ans[y] = 'A';
        }
    }

    for (int i = 1; i <= m; i++) {
        cout << ans[i];
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
}