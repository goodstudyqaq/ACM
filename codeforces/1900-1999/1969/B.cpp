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
    string s;
    cin >> s;
    int n = s.size();
    int now = 0;
    long long ans = 0;

    while (now < n && s[now] == '0') now++;

    int one = 0;
    while (now < n) {
        // debug(now);
        int go = now;
        while (go < n && s[go] == '1') go++;
        if (go == n) break;
        int len = go - now;
        one += len;

        int go2 = go;
        while (go2 < n && s[go2] == '0') go2++;
        int len2 = go2 - go;

        ans += 1LL * (one + 1) * len2;
        now = go2;
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