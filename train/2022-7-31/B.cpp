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
    vector<string> s(n);
    int one = 0;
    for (int i = 0; i < n; i++) {
        cin >> s[i];

        for (int j = 0; j < n; j++) {
            if (s[i][j] == '1') one++;
        }
    }

    auto work = [&](int x, int y) {
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (s[x][y] == '1') {
                res++;
            }
            x = (x + 1) % n;
            y = (y + 1) % n;
        }
        return res;
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, work(i, 0));
    }

    cout << n - ans + one - ans << endl;
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