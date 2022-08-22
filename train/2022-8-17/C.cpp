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
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<pii> V = {{1, 1}, {1, m}};
    int sz = V.size();
    vector<int> d(4);
    // int x1 = 3, y1 = 1, x2 = 2, y2 = 4;
    auto scan = [&](int x, int y) {
        cout << "SCAN " << x << ' ' << y << endl;
        fflush(stdout);
        // int res = abs(x - x1) + abs(y - y1) + abs(x - x2) + abs(y - y2);
        int res;
        cin >> res;
        return res;
    };
    auto dig = [&](int x, int y) {
        cout << "DIG " << x << ' ' << y << endl;
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };
    d[0] = scan(V[0].first, V[0].second);
    d[1] = scan(V[1].first, V[1].second);

    int sx = (d[0] + d[1] + 6 - 2 * m) / 2;
    int sy = (d[0] - d[1] + 2 + 2 * m) / 2;

    V.push_back({sx / 2, 1});
    V.push_back({1, sy / 2});
    d[2] = scan(V[2].first, V[2].second);
    d[3] = scan(V[3].first, V[3].second);

    int dx = d[2] - sy + 2;
    int dy = d[3] - sx + 2;

    int _x1 = (sx - dx) / 2;
    int _x2 = (sx + dx) / 2;
    int _y1 = (sy - dy) / 2;
    int _y2 = (sy + dy) / 2;
    debug(_x1, _x2, _y1, _y2);
    int res = dig(_x1, _y1);
    if (res == 1) {
        dig(_x2, _y2);
    } else {
        dig(_x1, _y2);
        dig(_x2, _y1);
    }
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}