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
    string s;
    cin >> s;
    int now = 0;
    long long ans = 0;
    long long up = 0;
    long long down = 0;
    while (now < n) {
        int go = now;
        while (go < n && s[go] == '1') {
            ans = max(ans, down + 1);
            go++;
        }
        int one_num = go - now;
        if (go == n) {
            break;
        }

        int go2 = go;
        while (go2 < n && s[go2] == '0') {
            go2++;
        }

        // [go, go2)
        long long tmp1 = 1LL * (go + go2 - 1) * (go2 - go) / 2;
        long long tmp2 = 1LL * (n - (go + 1) + n - go2) * (go2 - go) / 2;
        ans = max(ans, tmp1 + (one_num > 0));
        ans = max(ans, tmp2);
        if (one_num == 1) {
            ans = max(ans, tmp1 + down + 1);
        }
        up = tmp1;
        down = tmp2;
        now = go2;
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