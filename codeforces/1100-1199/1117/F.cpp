#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

    int n, p;
    cin >> n >> p;
    string s;
    cin >> s;
    vector<vector<int>> A(p, vector<int>(p));
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            cin >> A[i][j];
        }
    }

    int LIMIT = (1 << p);
    vector<int> dp(LIMIT, 1);
    vector<int> vis(LIMIT);

    function<void(int, int)> dfs = [&](int s, int s2) {
        if (vis[s]) return;
        vis[s] = 1;
        // if (dp[s] == 0) return;
        debug(s, s2);
        dp[s] = 0;

        for (int x = s; x; x ^= (x & -x)) {
            int y = x & -x;
            if (s2 & y) continue;
            dfs(s ^ y, s2);
        }
    };

    for (int i = 0; i < p; i++) {
        for (int j = i; j < p; j++) {
            if (A[i][j] == 1) continue;

            for (int k = 0; k < LIMIT; k++) {
                vis[k] = 0;
            }


            vector<int> idx;
            for (int k = 0; k < n; k++) {
                if (s[k] - 'a' == i || s[k] - 'a' == j) {
                    idx.push_back(k);
                }
            }

            int sz = idx.size();
            for (int k = 0; k < sz - 1; k++) {
                if (i == j || (i != j && s[idx[k]] != s[idx[k + 1]])) {
                    int status = 0;
                    for (int x = idx[k] + 1; x <= idx[k + 1] - 1; x++) {
                        int c = s[x] - 'a';
                        status |= (1 << c);
                    }
                    debug(status, i, j, idx[k], idx[k + 1]);
                    status = (LIMIT - 1) ^ status;
                    dfs(status, (1 << i) | (1 << j));
                }
            }
        }
    }
    debug(dp);

    // for (int i = LIMIT - 2; i >= 0; i--) {
    //     if (dp[i]) {
    //         bool ok = false;
    //         for (int j = 0; j < p; j++) {
    //             if ((i >> j) & 1) continue;
    //             if (dp[i + (1 << j)]) {
    //                 ok = true;
    //                 break;
    //             }
    //         }
    //         if (!ok) {
    //             dp[i] = 0;
    //         }
    //     }
    // }

    vector<int> cnt(26);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }

    int res = n;

    for (int i = 0; i < LIMIT; i++) {
        vis[i] = 0;
    }
    function<void(int)> dfs2 = [&](int s) {
        
        if (vis[s]) return;
        debug(s);
        vis[s] = 1;
        int sub = 0;
        for (int i = 0; i < 26; i++) {
            if ((s >> i) & 1) {
                sub += cnt[i];
            }
        }
        res = min(res, sub);

        for (int i = 0; i < 26; i++) {
            if ((s >> i) & 1) {
                if (dp[s - (1 << i)]) {
                    dfs2(s - (1 << i));
                }
            }
        }
    };

    dfs2(LIMIT - 1);
    cout << res << endl;
}