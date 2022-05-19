#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    int rt;
    vector<vector<int>> V(n + 1);
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        if (p == i) {
            rt = i;
        } else {
            V[p].push_back(i);
        }
    }

    vector<vector<int>> ans;

    function<void(int, vector<int> &)> dfs = [&](int u, vector<int> &now) {
        now.push_back(u);
        if (V[u].size() == 0) {
            ans.push_back(now);
            return;
        }
        for (int i = 0; i < V[u].size(); i++) {
            if (i == 0) {
                dfs(V[u][i], now);
            } else {
                vector<int> tmp;
                dfs(V[u][i], tmp);
            }
        }
    };

    vector<int> tmp;
    dfs(rt, tmp);
    cout << ans.size() << endl;
    for (auto v : ans) {
        cout << v.size() << endl;
        for (int j : v) {
            cout << j << ' ';
        }
        cout << endl;
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
}