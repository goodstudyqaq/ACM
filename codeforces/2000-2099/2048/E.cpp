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
    int n, m;
    cin >> n >> m;
    if (m >= 2 * n) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    // m <= 2n - 1

    if (n == 1) {
        cout << 1 << '\n'
             << 1 << '\n';
        return;
    }
    int M = 2 * n - 1;

    vector<int> ans(M);
    int now = 1;
    for (int i = 0; i < M; i += 2) {
        ans[i] = now;
        if (i + 1 < M) {
            ans[i + 1] = now;
        }
        now++;
    }
    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[j] << ' ';
        }
        cout << '\n';

        vector<int> dans(M);
        for (int j = 1; j < M; j++) {
            dans[j] = ans[j - 1];
        }

        if (ans[0] == ans[1]) {
            dans[0] = ans[M - 1];
        } else {
            dans[0] = dans[1];
        }
        ans = dans;
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