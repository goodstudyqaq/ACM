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
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    string color;
    cin >> color;
    int x = 0;
    for (int i = 0; i < n; i++) {
        if (color[i] == '?') x++;
    }
    vector<int> cnt(3);

    function<void(int, int)> dfs = [&](int u, int pre) {
        int leaf = true;
        for (auto v : V[u]) {
            if (v == pre) continue;
            leaf = false;
            dfs(v, u);
        }

        if (leaf) {
            if (color[u] == '?') {
                cnt[2]++;
            } else {
                cnt[color[u] - '0']++;
            }
        }
    };
    dfs(0, -1);

    if (color[0] != '?') {
        int f = color[0] - '0';
        cout << cnt[f ^ 1] + (cnt[2] + 1) / 2 << endl;
    } else {
        if (cnt[0] != cnt[1]) {
            int f = (cnt[1] > cnt[0]);
            cout << cnt[f] + cnt[2] / 2 << endl;
        } else {
            int y = x - 1 - cnt[2];
            if (y % 2) {
                cout << cnt[0] + (cnt[2] + 1) / 2 << endl;
            } else {
                cout << cnt[0] + cnt[2] / 2 << endl;
            }
        }
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
    return 0;
}