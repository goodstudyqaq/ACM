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
    int n;
    cin >> n;
    vector<long long> a(n + 1), b(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n + 1; i++) {
        cin >> b[i];
    }

    long long ans = 0;
    long long ans2 = 1e18;
    for (int i = 1; i <= n; i++) {
        ans += abs(a[i] - b[i]);

        if (a[i] <= b[n + 1] && b[n + 1] <= b[i]) {
            ans2 = 1;
        }
        if (b[i] <= b[n + 1] && b[n + 1] <= a[i]) {
            ans2 = 1;
        }

        ans2 = min({ans2, abs(a[i] - b[n + 1]) + 1, abs(b[i] - b[n + 1]) + 1});
    }
    cout << ans + ans2 << endl;

    

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