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
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    vector<int> cnt(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    for (int i = n - 1; i >= 1; i--) {
        cnt[i] += cnt[i + 1];
    }
    vector<long long> sum(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        sum[i] = sum[i + 1] + cnt[i];
    }
    debug(sum);

    long long ans = 0;
    for (int i = 0; i < m; i++) {
        int val = a[i];
        if (val == n) val = n - 1;
        int val2 = n - val;
        if (val < val2) {
            ans += sum[val2];
        } else {
            ans += sum[val2] - (val - val2 + 1);
        }
        debug(ans);
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