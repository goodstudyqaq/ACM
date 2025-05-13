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
    vector<vector<int>> a(n, vector<int>(n));
    int x = (n - 1) / 2, y = (n - 1) / 2;
    a[x][y] = 0;

    int d[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
    int now_f = 0;
    int now = 1;

    for (int i = 1; i < n; i++) {
        for (int t = 0; t < 2; t++) {
            for (int j = 0; j < i; j++) {
                x += d[now_f][0];
                y += d[now_f][1];
                a[x][y] = now++;
                // debug(x, y, now);
            }
            now_f = (now_f + 1) % 4;
        }
    }

    while (true) {
        x += d[now_f][0];
        y += d[now_f][1];
        if (x >= 0 && x < n && y >= 0 && y < n) {
            a[x][y] = now++;
        } else {
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
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