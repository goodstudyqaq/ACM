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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<string> s(n);
    vector<vector<int>> IDX(n, vector<int>(10));
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < 10; j++) {
            int v = s[i][j] - '0';
            IDX[i][v] = j;
        }
    }

    auto work = [&](int idx) {
        vector<int> vis(10);
        for (int i = 0; i < n; i++) {
            vis[IDX[i][idx]]++;
        }

        int mx = 0;
        int mx_idx = 0;
        for (int i = 0; i < 10; i++) {
            if (mx <= vis[i]) {
                mx = vis[i];
                mx_idx = i;
            }
        }
        return (mx - 1) * 10 + mx_idx;
    };

    int ans = 1e9;
    for (int i = 0; i < 10; i++) {
        ans = min(ans, work(i));
    }
    cout << ans << endl;
}