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
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) cin >> b[i];

    if (k == 1) {
        for (int i = 1; i <= n; i++) {
            if (b[i] != i) {
                cout << "NO" << endl;
                return;
            }
        }
        cout << "YES" << endl;
        return;
    }

    vector<int> vis(n + 1);
    vector<int> stk;
    function<bool(int)> dfs = [&](int u) {
        vis[u] = 1;
        int go = b[u];
        stk.push_back(u);
        bool ok = true;
        if (vis[go] == 0) {
            ok = dfs(go);
        } else if (vis[go] == 1) {
            int idx;
            for (int i = stk.size() - 1; i >= 0; i--) {
                if (stk[i] == go) {
                    idx = i;
                    break;
                }
            }
            int num = stk.size() - idx;
            if (num != k) ok = false;
        }
        vis[u] = 2;
        stk.pop_back();
        return ok;
    };
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            if (dfs(i) == false) {
                cout << "NO" << endl;
                return;
            }
        }
    }
    cout << "YES" << endl;
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