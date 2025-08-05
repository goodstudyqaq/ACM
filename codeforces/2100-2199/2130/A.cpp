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
    const int m = 50;
    vector<int> cnt(m + 1);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    int ans = 0;
    for (int i = 2; i <= m; i++) {
        ans += cnt[i] * i;
    }

    int mi = min(cnt[0], cnt[1]);

    ans += mi * 2;
    cnt[0] -= mi;
    cnt[1] -= mi;
    ans += cnt[1];
    ans += cnt[0];
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