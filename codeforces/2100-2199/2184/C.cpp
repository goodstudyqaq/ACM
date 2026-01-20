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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, k;
    cin >> n >> k;
    map<int, int> cache;

    function<int(int)> dfs = [&](int x) -> int {
        // debug(x);
        if (cache.count(x)) {
            return cache[x];
        }
        if (x < k) {
            return 1e9;
        }
        if (x == k) return 0;

        if (x % 2 == 0) {
            return cache[x] = dfs(x / 2) + 1;
        } else {
            return cache[x] = min(dfs(x / 2), dfs((x / 2) + 1)) + 1;
        }
    };


    int ans = dfs(n);
    if (ans >= 1e9) {
        ans = -1;
    }
    cout << ans << '\n';

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