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
    int n, k, d;
    cin >> n >> k >> d;
    vector<int> a(n + 1), b(k);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }

    int ans = 0;

    auto cal = [&]() {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] == i) res++;
        }
        return res;
    };

    for (int i = 0; i <= min(d - 1, 100000); i++) {
        int res = cal();

        int step = d - i - 1;
        res += step / 2;

        ans = max(res, ans);
        int r = b[i % k];
        for (int j = 1; j <= r; j++) {
            a[j]++;
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
    return 0;
}