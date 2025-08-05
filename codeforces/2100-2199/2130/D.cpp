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
    vector<int> p(n + 1);
    vector<int> idx(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        idx[p[i]] = i;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int _idx = idx[i];

        int res1 = 0;
        for (int j = 1; j < _idx; j++) {
            if (p[j] < i) continue;
            res1++;
        }

        int res2 = 0;
        for (int j = _idx + 1; j <= n; j++) {
            if (p[j] < i) continue;
            res2++;
        }
        ans += min(res1, res2);
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