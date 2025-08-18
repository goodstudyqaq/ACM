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
    int n, x;
    cin >> n >> x;
    string s;
    cin >> s;
    x--;
    if (x == 0 || x == n - 1) {
        cout << 1 << '\n';
        return;
    }

    if (s[x - 1] == '#' || s[x + 1] == '#') {
        cout << min(x + 1, n - x) << '\n';
    } else {
        // 封左边
        int ans1 = x + 1;

        // 往右边走

        int now = x + 1;
        while (now < n && s[now] == '.') {
            now++;
        }
        int ans2 = now == n ? 1 : n - now + 1;

        int res1 = min(ans1, ans2);

        // 封右边
        ans1 = n - x;
        now = x - 1;
        while (now >= 0 && s[now] == '.') {
            now--;
        }
        ans2 = now == -1 ? 1 : now + 1 + 1;
        int res2 = min(ans1, ans2);
        cout << max(res1, res2) << '\n';
    }
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