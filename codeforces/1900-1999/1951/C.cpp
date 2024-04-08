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
    int n, m, k;
    cin >> n >> m >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> f(n);
    iota(f.begin(), f.end(), 0);
    sort(f.begin(), f.end(), [&](int x, int y) {
        return a[x] < a[y];
    });

    int have = k;
    int now = 0;
    vector<int> cnt(n);
    while (have) {
        int idx = f[now];
        int use = min(have, m);
        cnt[idx] = use;
        have -= use;
        now++;
    }

    long long ans = 0;

    int use = 0;
    for (int i = 0; i < n; i++) {
        ans += 1LL * cnt[i] * a[i];
        ans += 1LL * cnt[i] * use;
        use += cnt[i];
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