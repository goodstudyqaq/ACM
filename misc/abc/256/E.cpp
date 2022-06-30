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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<int> x(n + 1), c(n + 1);
    vector<int> in(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        in[x[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    vector<int> vis(n + 1);

    queue<int> Q;

    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            Q.push(i);
        }
    }

    while (!Q.empty()) {
        auto u = Q.front();
        Q.pop();
        vis[u] = 2;
        in[x[u]]--;
        if (in[x[u]] == 0) {
            Q.push(x[u]);
        }
    }

    ll ans = 0;
    int mi;
    vector<pii> V;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        int nxt = x[u];
        mi = min(mi, c[u]);
        if (vis[nxt] == 2) {
            return;
        } else if (vis[nxt] == 1) {
            ans += mi;
            return;
        } else {
            dfs(nxt);
        }
        vis[u] = 2;
    };

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            mi = 1e9;
            dfs(i);
        }
    }
    cout << ans << endl;
}