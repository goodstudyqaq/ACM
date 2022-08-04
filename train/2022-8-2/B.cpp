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
int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<pii> V(n);
    map<pii, int> M;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        V[i] = {x, y};
        M[{x, y}] = i;
    }

    queue<int> Q;
    vector<pii> ans(n, {1e7, 1e7});
    vector<int> dis(n, 1e9);
    vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        auto [x, y] = V[i];
        int in = 0;
        for (int j = 0; j < 4; j++) {
            int x2 = x + d[j][0], y2 = y + d[j][1];
            if (M.count({x2, y2})) {
                in++;
            } else {
                ans[i] = {x2, y2};
            }
        }
        if (in < 4) {
            dis[i] = 1;
            Q.push(i);
        }
    }

    while (!Q.empty()) {
        int idx = Q.front();
        Q.pop();
        if (vis[idx]) continue;
        vis[idx] = true;
        auto [x, y] = V[idx];

        for (int i = 0; i < 4; i++) {
            int x2 = x + d[i][0], y2 = y + d[i][1];
            if (M.count({x2, y2})) {
                int idx2 = M[{x2, y2}];
                if (dis[idx2] > dis[idx] + 1) {
                    dis[idx2] = dis[idx] + 1;
                    ans[idx2] = ans[idx];
                    Q.push(idx2);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i].first << ' ' << ans[i].second << endl;
    }
    return 0;
}