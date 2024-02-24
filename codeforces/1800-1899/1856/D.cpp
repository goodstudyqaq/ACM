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
    int n;
    cin >> n;
    int now = n;
    map<pair<int, int>, int> cache;
    int limit = 5 * n * n;

    int cost = 0;

    auto ask = [&](int l, int r) {
        if (l == r) {
            return 0;
        }

        if (cache.count({l, r})) {
            return cache[{l, r}];
        }

        cout << "? " << l << ' ' << r << endl;
        fflush(stdout);
        int ans;
        cin >> ans;
        cache[{l, r}] = ans;
        cost += (r - l) * (r - l);
        return ans;
    };

    function<int(int, int)> work = [&](int l, int r) {
        int m = l + r >> 1;
        if (l == r) {
            return l;
        }
        int idx1 = work(l, m);
        int idx2 = work(m + 1, r);

        int v1 = ask(idx1, idx2);
        int v2 = ask(idx1, idx2 - 1);
        if (v1 == v2) {
            return idx2;
        } else {
            return idx1;
        }
    };
    int res = work(1, n);

    cout << "! " << res << endl;
    fflush(stdout);

    debug("use", limit, cost);
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
    return 0;
}