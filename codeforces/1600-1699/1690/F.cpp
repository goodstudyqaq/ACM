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
    string s;
    cin >> n >> s;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    vector<bool> vis(n);
    ll ans = 1;
    string new_s;

    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        new_s += s[u];
        int nxt = p[u];
        if (vis[nxt] == 0) {
            dfs(nxt);
        }
    };

    auto get_val = [&]() -> ll {
        int sz = new_s.size();
        string ss = new_s + new_s;
        for (int i = 1; i < sz; i++) {
            string tmp = ss.substr(i, sz);
            if (tmp == new_s) {
                return i;
            }
        }
        return sz;
    };

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            new_s = "";
            dfs(i);

            ll val = get_val();
            ll g = __gcd(val, ans);
            ans = ans * val / g;
        }
    }
    cout << ans << endl;
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