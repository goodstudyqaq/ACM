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
    int N, K;
    cin >> N >> K;
    vector<int> status(N);
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        int n = s.size();
        int s1 = 0;
        for (int j = 0; j < n; j++) {
            int tmp = s[j] - 'a';
            s1 = s1 | (1 << tmp);
        }
        status[i] = s1;
    }

    int LIMIT = 1 << N;
    int res = 0;

    for (int i = 1; i < LIMIT; i++) {
        vector<int> vis(26, 0);

        for (int j = 0; j < N; j++) {
            if ((i >> j) & 1) {
                for (int k = 0; k < 26; k++) {
                    if ((status[j] >> k) & 1) {
                        vis[k]++;
                    }
                }
            }
        }
        debug(i, vis);

        int num = 0;
        for (int j = 0; j < 26; j++) {
            if (vis[j] == K) {
                num++;
            }
        }
        res = max(res, num);
    }
    cout << res << endl;
    return 0;
}