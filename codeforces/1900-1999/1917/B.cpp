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
    string s;
    cin >> s;

    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    // if (n == 2) {
    //     if (s[0] == s[1])
    //         cout << 2 << endl;
    //     else
    //         cout << 3 << endl;
    //     return;
    // }

    vector<vector<long long>> dp(26, vector<long long>(n + 1, 0));
    function<void(char c, int idx)> work = [&](char c, int idx) {
        if (dp[c - 'a'][idx] == 1) return;
        dp[c - 'a'][idx] = 1;
        if (idx == n) return;
        work(c, idx + 1);
        work(s[idx], idx + 1);
    };
    work(s[0], 1);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            if (dp[j][i]) ans++;
        }
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