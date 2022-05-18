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

vector<vector<int>> vis;
vector<vector<int>> vis2;
int offset;
void draw1(int R) {
    for (int i = -R; i <= R; i++) {
        for (int j = -R; j <= R; j++) {
            double s = round(sqrt(1.0 * i * i + 1.0 * j * j));
            if (s <= R) {
                vis[i + offset][j + offset] = 1;
            }
        }
    }
}

void draw3(int R) {
    for (int x = -R; x <= R; x++) {
        int y = round(sqrt(1.0 * R * R - 1.0 * x * x));
        vis2[x + offset][y + offset] = 1;
        vis2[x + offset][-y + offset] = 1;
        vis2[y + offset][x + offset] = 1;
        vis2[-y + offset][x + offset] = 1;
    }
}

void draw2(int R) {
    for (int r = 0; r <= R; r++) {
        draw3(r);
    }
}

void solve() {
    int R;
    cin >> R;
    offset = R;
    vis = vector(2 * R + 1, vector(2 * R + 1, 0));
    vis2 = vector(2 * R + 1, vector(2 * R + 1, 0));
    // vis.resize(2 * R + 1, vector<int>(2 * R + 1));
    // vis2.resize(2 * R + 1, vector<int>(2 * R + 1));
    for (int i = -R; i <= R; i++) {
        for (int j = -R; j <= R; j++) {
            vis[i + offset][j + offset] = vis2[i + offset][j + offset] = 0;
        }
    }
    draw1(R);
    draw2(R);
    int ans = 0;
    // debug(R);
    for (int i = -R; i <= R; i++) {
        for (int j = -R; j <= R; j++) {
            if (vis[i + offset][j + offset] != vis2[i + offset][j + offset]) {
                ans++;
            }
        }
    }
    debug(ans);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}