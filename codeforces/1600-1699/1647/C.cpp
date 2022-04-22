#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<string> mp(n);
        for (int i = 0; i < n; i++) {
            cin >> mp[i];
        }

        typedef pair<int, int> pp;
        typedef pair<pp, pp> ppp;
        vector<ppp> ans;

        if (mp[0][0] == '1') {
            cout << -1 << endl;
            continue;
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (mp[i][j] == '1') {
                    if (j == 0) continue;
                    ans.push_back({{i, j - 1}, {i, j}});
                }
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            if (mp[i][0] == '1') {
                ans.push_back({{i - 1, 0}, {i, 0}});
            }
        }
        cout << ans.size() << endl;
        for (auto it : ans) {
            cout << it.first.first + 1 << ' ' << it.first.second + 1 << ' ' << it.second.first + 1 << ' ' << it.second.second + 1 << endl;
        }
    }
    return 0;
}