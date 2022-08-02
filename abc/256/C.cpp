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
    vector<int> h(3), w(3);
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        cin >> h[i];
        sum += h[i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> w[i];
        sum -= w[i];
    }
    if (sum) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 0; i < 3; i++) {
        h[i] -= 3;
        w[i] -= 3;
    }

    int ans = 0;
    function<void(int)> dfs = [&](int idx) {
        int x = idx / 3, y = idx % 3;

        for (int i = 0; i < x; i++) {
            if (h[i]) return;
        }
        if (x == 2) {
            for (int i = 0; i < y; i++) {
                if (w[i]) return;
            }
        }

        if (x == 2 && y == 2) {
            if (h[2] != w[2]) return;
            for (int i = 0; i < 2; i++) {
                if (h[i] != 0) return;
                if (w[i] != 0) return;
            }
            ans++;

            return;
        }

        int mi = min(h[x], w[y]);
        for (int i = 0; i <= mi; i++) {
            h[x] -= i, w[y] -= i;
            dfs(idx + 1);
            h[x] += i, w[y] += i;
        }
    };

    dfs(0);
    cout << ans << endl;
}