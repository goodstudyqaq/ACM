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
    map<int, int> M;
    int ans = 0;
    for (int i = 0; i < n * 2; i++) {
        int a;
        cin >> a;
        M[a]++;
    }
    int cnt = 0;
    int cnt2 = 0;
    for (auto it : M) {
        if (it.second % 2 == 0) {
            int tmp = it.second / 2;
            if (tmp % 2 == 0) {
                cnt++;
            } else {
                ans += 2;
            }
        } else {
            cnt2++;
        }
    }

    if (cnt2 < 2) {
        ans += cnt2;
        if (cnt % 2) {
            ans += (cnt - 1) * 2;
        } else {
            ans += cnt * 2;
        }
    } else {
        ans += cnt2 + cnt * 2;
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