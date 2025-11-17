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
    int h, d;
    cin >> h >> d;
    int add = 0;
    if (h == 1) {
        add++;
        h++;
    }
    int l = 0, r = d - 1;
    int ans = -1;

    auto check = [&](int num) -> bool {
        // 有 num 个 空，那么把 d 分成了 num + 1 段
        int val = d / (num + 1);
        int left = d % (num + 1);

        // left 个 val + 1, num + 1 - left 个 val
        long long ct = 1LL * left * (1 + val + 1) * (val + 1) / 2 + 1LL * (num + 1 - left) * (1 + val) * val / 2;
        return ct < h + num;
    };

    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans + d + add << '\n';
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