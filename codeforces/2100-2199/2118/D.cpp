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
    int n, k;
    cin >> n >> k;

    vector<long long> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    vector<vector<int>> V(n + 1, vector<int>(2, -1));
    vector<vector<int>> vis(n + 1, vector<int>(2, 0));
    vector<vector<int>> circle(n + 1, vector<int>(2, 0));

    auto check = [&](int i, int j) -> bool {
        long long dis = abs(p[i] - p[j]);
        dis %= k;
        if ((dis + d[i]) % k == d[j]) {
            return true;
        }
        return false;
    };

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (check(i, j)) {
                V[i][1] = j;
                break;
            }
        }

        for (int j = i - 1; j >= 1; j--) {
            if (check(i, j)) {
                V[i][0] = j;
                break;
            }
        }
    }
    // debug(V);

    vector<pii> stk;

    function<void(int, int)> dfs = [&](int u, int dir) {
        vis[u][dir] = 1;
        stk.push_back({u, dir});

        int go = V[u][dir];
        if (go == -1) {
            return;
        }

        int go2 = V[go][dir ^ 1];
        if (go2 == -1) {
            return;
        }

        if (vis[go][dir ^ 1] == 2) {
            return;
        }

        if (vis[go][dir ^ 1] == 1) {
            for (auto it : stk) {
                circle[it.first][it.second] = 1;
            }
            return;
        }
        dfs(go, dir ^ 1);
        vis[u][dir] = 2;
    };

    for (int i = 1; i <= n; i++) {
        if (V[i][0] != -1 && vis[i][0] == 0) {
            stk.clear();
            dfs(i, 0);
        }
    }
    // debug(circle);

    int q;
    cin >> q;

    while (q--) {
        long long a;
        cin >> a;
        bool ok = true;
        for (int i = 1; i <= n; i++) {
            if (p[i] >= a) {
                long long dis = p[i] - a;
                dis %= k;
                if (dis % k == d[i]) {
                    if (circle[i][0]) {
                        ok = false;
                    }
                    break;
                }
            }
        }
        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
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