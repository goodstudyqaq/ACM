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

    int N;
    cin >> N;
    vector<string> s;
    s.resize(N);

    int ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    ax--, ay--, bx--, by--;

    for (int i = 0; i < N; i++) {
        cin >> s[i];
    }
    if ((ax + ay) % 2 != (bx + by) % 2) {
        cout << -1 << endl;
        return 0;
    }

    // set<int> S1, S2;

    typedef pair<int, int> pii;
    vector<vector<int>> dis;
    const int inf = numeric_limits<int>::max() / 2;
    dis.resize(N, vector<int>(N, inf));
    queue<pii> Q;
    Q.push({ax, ay});
    dis[ax][ay] = 0;
    int d[4][2] = {1, 1, 1, -1, -1, 1, -1, -1};

    while (!Q.empty()) {
        auto it = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++) {
            for (int l = 1;; l++) {
                int tmpx = it.first + d[i][0] * l;
                int tmpy = it.second + d[i][1] * l;
                if (tmpx < 0 || tmpx >= N || tmpy < 0 || tmpy >= N) break;
                if (s[tmpx][tmpy] == '#') break;

                if (dis[tmpx][tmpy] > dis[it.first][it.second] + 1) {
                    dis[tmpx][tmpy] = dis[it.first][it.second] + 1;
                    Q.push({tmpx, tmpy});
                } else if (dis[tmpx][tmpy] < dis[it.first][it.second] + 1) {
                    break;
                }
            }
        }
    }
    debug(dis);
    if (dis[bx][by] == inf) dis[bx][by] = -1;
    cout << dis[bx][by] << endl;

    return 0;
}