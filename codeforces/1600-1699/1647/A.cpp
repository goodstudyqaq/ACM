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
        vector<vector<int>> mp1(n + 1, vector<int>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mp1[i][j] = mp[i][j] - '0';
            }
        }
        bool flag = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int res = mp1[i][j] + mp1[i + 1][j] + mp1[i][j + 1] + mp1[i + 1][j + 1];
                if (res == 3) {
                    i = n + 10;
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    return 0;
}