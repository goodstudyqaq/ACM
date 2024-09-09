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
    vector<int> p(n + 1);
    vector<vector<int>> V(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        V[i].push_back(p[i]);
    }
    string s;
    cin >> s;

    vector<int> ans(n + 1, -1);

    int black_num = 0;
    vector<int> vis(n + 1);
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        if (s[u - 1] == '0') black_num++;

        int go = V[u][0];
        if (vis[go] == 0) {
            dfs(go);
        }
        ans[u] = black_num;
    };

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            black_num = 0;
            dfs(i);
        }
        cout << ans[i] << ' ';
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
    return 0;
}