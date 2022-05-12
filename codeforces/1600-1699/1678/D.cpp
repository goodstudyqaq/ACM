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
    string s;
    cin >> n >> m >> s;
    vector<int> ans(n * m + 1);
    vector<int> sum(n * m + 1);
    for (int i = 0; i < n * m; i++) {
        sum[i + 1] = sum[i] + s[i] - '0';
    }
    for (int i = 1; i <= n * m; i++) {
        int val = sum[i] - sum[max(0, i - m)];
        if (i > m) ans[i] = ans[i - m];
        ans[i] += (val > 0);
    }

    vector<bool> vis(m);
    int num = 0;

    for (int i = 0; i < n * m; i++) {
        if (s[i] == '1') {
            int tmp = i % m;
            if (vis[tmp] == 0) {
                vis[tmp] = 1;
                num++;
            }
        }
        ans[i + 1] += num;
    }

    for (int i = 1; i <= n * m; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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