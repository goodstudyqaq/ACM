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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> cnt(n + 1);
    for (int i = 1; i <= m; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    int l = 1, r = 2 * m;
    int ans = -1;

    auto check = [&](int time) {
        ll t2 = 0;
        for (int i = 1; i <= n; i++) {
            int have = cnt[i];
            int can = min(have, time);
            int have_time = time - can;
            int have_work = have - can;
            if (have_time) {
                int tmp = have_time / 2;
                t2 -= tmp;
            } else {
                t2 += have_work;
            }
        }
        return t2 <= 0;
    };

    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
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
}