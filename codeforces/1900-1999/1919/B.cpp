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
    const int inf = numeric_limits<int>::max() / 2;
    vector<int> dp(n + 1, inf), a(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = (s[i - 1] == '+' ? 1 : -1);
        sum[i] = sum[i - 1] + a[i];
    }
    cout << abs(sum[n]) << endl;
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