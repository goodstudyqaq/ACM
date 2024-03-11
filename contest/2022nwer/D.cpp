#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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

    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    const double inf = 1e9;
    int N = 2 * n + 1;
    int M = 2 * m + 1;
    vector<vector<double>> dp(N, vector<double>(M, inf));
    dp[0][0] = 0;

    typedef pair<int, int> pii;
    typedef pair<double, pii> pdii;
    priority_queue<pdii, vector<pdii>, greater<pdii>> Q;
    Q.push(pdii(0.0, pii(0, 0)));

    int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
    vector<vector<int>> vis(N, vector<int>(M, 0));
    const double pi = acos(-1);
    double circle_d = pi * 2.5;

    while (!Q.empty()) {
        auto it = Q.top();
        Q.pop();
        double dis = it.first;

        int x = it.second.first;
        int y = it.second.second;
        if (vis[x][y]) continue;
        vis[x][y] = 1;

        int idxx = x / 2;
        int idxy = y / 2;
        debug(dis, x, y, idxx, idxy);
        if (x % 2 == 0 && y % 2 == 0) {
            // 可以到出走
            for (int i = 0; i < 4; i++) {
                int x2 = x + d[i][0], y2 = y + d[i][1];
                if (x2 >= 0 && x2 < N && y2 >= 0 && y2 < M) {
                    if (dp[x2][y2] > dp[x][y] + 5) {
                        dp[x2][y2] = dp[x][y] + 5;
                        Q.push(pdii(dp[x2][y2], pii(x2, y2)));
                    }
                }
            }
        }
        if (x % 2) {
            for (int i = -1; i <= 1; i++) {
                if (i == 0) continue;
                int x2 = x + i;
                if (dp[x2][y] > dp[x][y] + 5) {
                    dp[x2][y] = dp[x][y] + 5;
                    Q.push(pdii(dp[x2][y], pii(x2, y)));
                }
            }

            if (s[idxx][idxy] == 'O') {
                int y2 = y + 1;
                for (int i = -1; i <= 1; i++) {
                    if (i == 0) continue;
                    int x2 = x + i;
                    if (dp[x2][y2] > dp[x][y] + circle_d) {
                        dp[x2][y2] = dp[x][y] + circle_d;
                        Q.push(pdii(dp[x2][y2], pii(x2, y2)));
                    }
                }
            }
            if (idxy - 1 >= 0 && s[idxx][idxy - 1] == 'O') {
                int y2 = y - 1;
                for (int i = -1; i <= 1; i++) {
                    if (i == 0) continue;
                    int x2 = x + i;
                    if (dp[x2][y2] > dp[x][y] + circle_d) {
                        dp[x2][y2] = dp[x][y] + circle_d;
                        Q.push(pdii(dp[x2][y2], pii(x2, y2)));
                    }
                }
            }

        } 
        if (y % 2) {
            for (int i = -1; i <= 1; i++) {
                if (i == 0) continue;
                int y2 = y + i;
                if (dp[x][y2] > dp[x][y] + 5) {
                    dp[x][y2] = dp[x][y] + 5;
                    Q.push(pdii(dp[x][y2], pii(x, y2)));
                }
            }
            if (x != N - 1 && s[idxx][idxy] == 'O') {
                int x2 = x + 1;
                for (int i = -1; i <= 1; i++) {
                    if (i == 0) continue;
                    int y2 = y + i;
                    if (dp[x2][y2] > dp[x][y] + circle_d) {
                        dp[x2][y2] = dp[x][y] + circle_d;
                        Q.push(pdii(dp[x2][y2], pii(x2, y2)));
                    }
                }
            }
            if (idxx - 1 >= 0 && s[idxx - 1][idxy] == 'O') {
                int x2 = x - 1;
                for (int i = -1; i <= 1; i++) {
                    if (i == 0) continue;
                    int y2 = y + i;
                    if (dp[x2][y2] > dp[x][y] + circle_d) {
                        dp[x2][y2] = dp[x][y] + circle_d;
                        Q.push(pdii(dp[x2][y2], pii(x2, y2)));
                    }
                }
            }
        }
    }

    cout << dp[2 * n][2 * m] << endl;
}