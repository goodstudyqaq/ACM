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

typedef pair<int, int> pii;
void solve() {
    int N, M;
    cin >> N >> M;
    int mx = max(N, M);
    vector vis = vector(2, vector(4 * mx + 1, 0));
    queue<pii> Q;
    vector<pii> ans;
    Q.push({1, 1});
    ans.push_back({1, 1});
    vis[0][4] = vis[1][4] = 1;
    int d[2][2] = {1, 0, 0, 1};

    while (!Q.empty()) {
        auto it = Q.front();
        Q.pop();
        for (int i = 0; i < 2; i++) {
            int tmpx = it.first + d[i][0], tmpy = it.second + d[i][1];
            if (tmpx >= 1 && tmpx <= N && tmpy >= 1 && tmpy <= M && vis[0][3 * tmpx + tmpy] == 0 && vis[1][tmpx + 3 * tmpy] == 0) {
                Q.push({tmpx, tmpy});
                vis[0][3 * tmpx + tmpy] = 1;
                vis[1][tmpx + 3 * tmpy] = 1;
                ans.push_back({tmpx, tmpy});
            }
        }
    }
    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it.first << ' ' << it.second << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    solve();
}