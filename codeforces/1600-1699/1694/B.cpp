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
    string s;
    cin >> n >> s;

    vector<int> diff(n + 1);

    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1) {
            diff[i] = 1;
            continue;
        }
        diff[i] = diff[i + 1];
        if (s[i] != s[i + 1]) {
            diff[i]++;
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += diff[i];
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