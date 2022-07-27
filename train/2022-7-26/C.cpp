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
    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        V[p].push_back(i);
    }
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll ans = 0;

    function<pll(int)> dfs = [&](int u) -> pll {
        pll res;
        if (V[u].size() == 0) {
            res = {a[u], 1};
        } else {
            res = {a[u], 0};
        }
        for (auto it : V[u]) {
            pll tmp = dfs(it);
            res.first += tmp.first;
            res.second += tmp.second;
        }
        debug(u, res);
        ans = max(ans, (res.first + res.second - 1) / res.second);
        return res;
    };
    dfs(1);
    cout << ans << endl;

    return 0;
}