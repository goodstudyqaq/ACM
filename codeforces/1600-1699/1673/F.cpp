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
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    // freopen("./data.in", "r", stdin);
#endif
    int n, k;
    cin >> n >> k;
    vector idx = vector(2, vector(2, 0));

    idx[0][0] = 0, idx[0][1] = 2, idx[1][0] = 1, idx[1][1] = 3;

    auto work = [&](int b) {
        int n = idx.size();
        int m = n * 2;
        idx.resize(m);

        for (int i = 0; i < m; i++) {
            idx[i].resize(m);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int val = idx[i][j];
                idx[i][m - 1 - j] = (2 << b) + val;
                idx[m - 1 - i][j] = (1 << b) + val;
                idx[m - 1 - i][m - 1 - j] = (3 << b) + val;
            }
        }
    };

    for (int i = 1; i <= 4; i++) {
        work(2 * i);
    }
    int ct = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            int idx1 = idx[i][j], idx2 = idx[i][j + 1];
            ct += (idx1 ^ idx2);
            cout << (idx1 ^ idx2) << " \n"[j == n - 2];
        }
        fflush(stdout);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            int idx1 = idx[i][j], idx2 = idx[i + 1][j];
            ct += (idx1 ^ idx2);
            cout << (idx1 ^ idx2) << " \n"[j == n - 1];
        }
        fflush(stdout);
    }
    debug(ct);

    typedef pair<int, int> pii;
    map<int, pii> loc;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            loc[idx[i][j]] = {i, j};
        }
    }

    int x = 0, y = 0;
    while (k--) {
        int val;
        cin >> val;
        int tmp = val ^ idx[x][y];
        pii res = loc[tmp];
        cout << res.first + 1 << ' ' << res.second + 1 << endl;
        x = res.first, y = res.second;
        fflush(stdout);
    }
    return 0;
}