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
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long ans = 0;

    for (int i = 1; i < n; i += 2) {
        int left = i - 1;
        if (a[i] < a[left]) {
            ans += a[left] - a[i];
            a[left] = a[i];
        }
        if (i + 1 < n && a[i] < a[i + 1]) {
            ans += a[i + 1] - a[i];
            a[i + 1] = a[i];
        }

        if (i + 1 < n && a[i] < a[left] + a[i + 1]) {
            int need = a[left] + a[i + 1] - a[i];
            a[i + 1] -= need;
            ans += need;
        }
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