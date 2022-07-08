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
    vector a = vector(n, vector(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    int step = n + m - 1;
    if (step % 2) {
        cout << "NO" << endl;
        return;
    }
    bool flag = false;
    vector<vector<set<int>>> vis = vector(n, vector(m, set<int>{}));

    // vector vis = vector(n, vector(m, vector(offset * 2, 0)));
    int d[2][2] = {1, 0, 0, 1};

    function<void(int, int, int)>
        dfs = [&](int x, int y, int sum) {
            if (vis[x][y].count(sum)) return;
            vis[x][y].insert(sum);
            if (x == n - 1 && y == m - 1) {
                if (sum == 0) {
                    flag = true;
                }
                return;
            }
            if (flag) return;

            int step_num = n - x + m - y - 2;
            if (sum - step_num > 0) return;
            if (sum + step_num < 0) return;

            for (int i = 0; i < 2; i++) {
                int nxt_x = x + d[i][0], nxt_y = y + d[i][1];
                if (nxt_x < n && nxt_y < m) {
                    dfs(nxt_x, nxt_y, sum + a[nxt_x][nxt_y]);
                }
            }
        };
    dfs(0, 0, a[0][0]);
    if (flag) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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