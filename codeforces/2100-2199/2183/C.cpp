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
    int n, m, k;
    cin >> n >> m >> k;

    int left = k - 1;
    int right = n - k;

    int mx = max(left, right);
    int mi = min(left, right);

    int need = mx + mx - 1 + mi;

    if (m >= need) {
        cout << n << '\n';
        return;
    }

    int ans = 1;
    for (int i = 0; i <= mx; i++) {
        int use = i;
        if (i) {
            use += i - 1;  // 准备
        }
        int left = m - use;
        if (left > use) continue;
        int have = i;
        int tmp = min({have, mi, left});
        ans = max(ans, tmp + i + 1);



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