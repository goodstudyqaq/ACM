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
    int n, m, k;
    cin >> n >> m >> k;
    int w;
    cin >> w;
    vector<int> a(w);
    for (int i = 0; i < w; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    vector<int> times(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = max(0, i - k + 1);
            int d = min(i,  n - k);
            int l = max(0, j - k + 1);
            int r = min(j, m - k);
            times[i * m + j] = 1LL * (d - u + 1) * (r - l + 1);
            // debug(i, j, times[i * m + j]);
        }
    }
    
    sort(times.begin(), times.end());
    long long ans = 0;
    for (int i = n * m - w; i < n * m; i++) {
        ans += 1LL * times[i] * a[i - n * m + w];
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