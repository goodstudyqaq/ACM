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
    int n, x, y;
    cin >> n >> x >> y;

    function<ll(int, ll, int)> dfs = [&](int dep, ll num, bool flag) -> ll {
        // debug(dep, num, flag);
        if (dep == 1) {
            if (flag == 0) return 0;
            return num;
        }

        if (flag == 0) {
            // red
            return dfs(dep - 1, num, 0) + dfs(dep, num * x, 1);
        } else {
            // blue
            return dfs(dep - 1, num, 0) + dfs(dep - 1, num * y, 1);
        }
    };

    cout << dfs(n, 1, 0) << endl;
    return 0;
}