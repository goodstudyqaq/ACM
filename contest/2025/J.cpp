#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    int mx_t = 0;
    typedef pair<int, int> pii;
    vector<pair<int, int>> V(n);
    for (int i = 0; i < n; i++) {
        int a, b, c, t;
        cin >> a >> b >> c >> t;
        int sum = a + b + c;
        mx_t = max(mx_t, t);
        V[i] = {sum, t};
    }
    sort(V.begin(), V.end(), [&](pii a, pii b) {  return a.second < b.second; });
    debug(V);
    const int inf = 1e9;
    vector<int> dp(mx_t + 1, -inf);

    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = V[i].second; j - V[i].first >= 0; j--) {
            dp[j] = max(dp[j], dp[j - V[i].first] + 1);
        }
    }

    int res = 0;
    for (int i = 0; i <= mx_t; i++) {
        res = max(res, dp[i]);
    }
    cout << res << '\n';
}