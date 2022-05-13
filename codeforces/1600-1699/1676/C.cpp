#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    auto work = [&](int a, int b) -> int {
        int res = 0;
        for (int i = 0; i < m; i++) {
            char it1 = s[a][i], it2 = s[b][i];
            res += abs(it1 - it2);
        }
        return res;
    };

    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = min(ans, work(i, j));
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
}