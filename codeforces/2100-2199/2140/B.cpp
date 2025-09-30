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
    int x;
    cin >> x;

    vector<int> v;

    while (x) {
        v.push_back(x % 10);
        x /= 10;
    }

    reverse(v.begin(), v.end());
    int ans = 0;
    if (v[0] == 9) {
        ans = 9;
    }
    for (int i = 0; i < v.size(); i++) {
        ans = ans * 10 + (9 - v[i]);
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