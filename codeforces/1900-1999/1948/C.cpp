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
    vector<string> s(2);
    cin >> n;
    cin >> s[0] >> s[1];
    vector<vector<int>> vis(2, vector<int>(n, 0));
    vis[0][0] = 1;
    typedef pair<int, int> pii;
    queue<pii> Q;
    Q.push({0, 0});

    int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

    while (!Q.empty()) {
        auto it = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++) {
            int x2 = it.first + d[i][0];
            int y2 = it.second + d[i][1];
            if (x2 >= 0 && x2 < 2 && y2 >= 0 && y2 < n) {
                if (s[x2][y2] == '>') {
                    y2++;
                } else {
                    y2--;
                }
                if (vis[x2][y2] == 0) {
                    vis[x2][y2] = 1;
                    Q.push({x2, y2});
                }
            }
        }
    }

    if (vis[1][n - 1]) {
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
    return 0;
}