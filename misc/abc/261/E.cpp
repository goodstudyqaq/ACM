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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, c;
    cin >> n >> c;
    vector<pii> V(n + 1);
    for (int i = 1; i <= n; i++) {
        int t, a;
        cin >> t >> a;
        V[i] = {t, a};
    }

    auto work = [&](int x, int y, int type) {
        if (type == 1) {
            return x & y;
        } else if (type == 2) {
            return x | y;
        } else {
            return x ^ y;
        }
    };

    vector<vector<vector<int>>> result = vector(30, vector(n + 1, vector(2, 0)));
    // result[i][j][0]
    for (int i = 0; i < 30; i++) {
        int x = 0, y = 1;
        for (int j = 1; j <= n; j++) {
            auto it = V[j];
            int val = (it.second >> i) & 1;
            x = work(x, val, it.first);
            y = work(y, val, it.first);
            result[i][j][0] = x;
            result[i][j][1] = y;
        }
    }

    vector<int> res(n + 1);
    for (int j = 0; j < 30; j++) {
        int now = (c >> j) & 1;
        for (int i = 1; i <= n; i++) {
            int val = result[j][i][now];
            // if (val) {
            //     debug(j, i);
            // }
            if (val) {
                res[i] |= (1 << j);
            }
            now = val;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << endl;
    }

    return 0;
}