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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<pii> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = {min(a[i], b[i]), max(a[i], b[i])};
    }
    sort(v.begin(), v.end());

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        auto [x, y] = v[i];
        sum += y - x;
    }

    long long ans = numeric_limits<long long>::max() / 2;
    for (int i = 0; i < n - 1; i++) {
        auto [x, y] = v[i];
        auto [x2, y2] = v[i + 1];
        if (x2 <= y) {
            cout << sum << '\n';
            return;
        }

        long long tmp = sum - (y - x) - (y2 - x2) + (x2 + y2 - x - y);
        ans = min(ans, tmp);
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