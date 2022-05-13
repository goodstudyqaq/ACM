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
    map<int, int> m1, m2;

    vector mp = vector(n, vector(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a;
            cin >> a;
            mp[i][j] = a;
            m1[i + j] += a;
            m2[i - j] += a;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int t1 = i + j;
            int t2 = i - j;
            int tmp = m1[t1] + m2[t2] - mp[i][j];
            ans = max(ans, tmp);
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