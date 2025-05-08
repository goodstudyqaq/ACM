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
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;

    auto get_v = [&](int l, int r) -> vector<int> {
        int now = l;
        vector<int> res;
        while (now < r) {
            // debug(now, r);
            for (int i = 19; i >= 0; i--) {
                if (now % (1 << i) == 0 && now + (1 << i) <= r) {
                    res.push_back(1 << i);
                    now += (1 << i);
                    break;
                }
            }
        }
        return res;
    };

    auto v1 = get_v(l1, r1);
    auto v2 = get_v(l2, r2);

    int res = 0;
    for (auto it1 : v1) {
        for (auto it2 : v2) {
            res += max(it1, it2) / min(it1, it2);
        }
    }
    cout << res << '\n';
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