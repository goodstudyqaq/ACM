#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    int n;
    cin >> n;
    vector<vector<long long>> val(3, vector<long long>(n + 1));
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> val[0][i];
        sum += val[0][i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> val[1][i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> val[2][i];
    }
    long long limit = (sum + 2) / 3;

    vector<int> p(3);
    iota(p.begin(), p.end(), 0);


    do {
        int now = 1;
        bool flag = true;
        vector<int> V;
        for (int i = 0; i < 3; i++) {
            int idx = p[i];
            long long now_val = 0;
            while (now <= n && now_val < limit) {
                now_val += val[idx][now];
                now++;
            }
            if (now_val < limit) {
                flag = false;
                break;
            }
            V.push_back(now);
        }
        debug(V);
        if (flag) {
            vector<int> ans(3), ansl(3);
            for (int i = 0; i < 3; i++) {
                ans[p[i]] = V[i] - 1;
                if (i == 0) {
                    ansl[p[i]] = 1;
                } else {
                    ansl[p[i]] = ans[p[i - 1]] + 1;
                }
            }
            // debug(ans);
            for (int i = 0; i < 3; i++) {
                cout << ansl[i] << ' ' << ans[i] << ' ';
            }
            cout << endl;
            return;
        }
    } while (next_permutation(p.begin(), p.end()));

    cout << -1 << endl;

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